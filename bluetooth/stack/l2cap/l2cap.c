/*
  Copyright 2013-2014 bcstack.org

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "bluetooth.h"

#define INTERNAL_SENDCFG_REQUEST   0xF0

#define SIG_OUTPUT          0x01
#define SDP_OUTPUT          0x02
#define ATT_OUTPUT          0x04
#define RFCOMM_OUTPUT       0x08
#define VPORT_OUTPUT        0x10

#if DEBUG_L2CAP
#define l2cap_printf printf
#else
#define l2cap_printf(...)
#endif

static struct {
    u8  outputs;
#ifdef EXPERIMENTAL
    u16 sdp_cid;
    u16 rfcomm_cid;
#endif // EXPERIMENTAL
    u16 vport_cid;
    u16 offset;
    u16 length;
    u8  buffer[CFG_L2CAP_MTU_EDR];

    struct {
        u8 code;
        u8 id;

        union {
            struct {
                u16 psm;
                u16 scid;
            } connection;

            struct {
                u16 dcid;
                u16 flags;
            } configure;

            struct {
                u16 dcid;
                u16 scid;
            } disconnection;

            struct {
                u16 type;
            } info;
        } u;
    } request;
} l2cap;

static u8 l2cap_sig_input(u8* input, u16 isize);
static u8 l2cap_sig_output(u8* output, u16* osize);
u8 l2cap_sig_input(u8* input, u16 isize);
u8 l2cap_sig_output(u8* output, u16* osize);
u8 vport_input(u8* input, u16 isize);
u8 vport_output(u8* output, u16* osize);

void l2cap_init()
{
    memset(&l2cap, 0, sizeof(l2cap));
}

u8 l2cap_input(u8* input, u16 isize, u8 flags)
{
    u8 l2len;
    u16 cid;
    u8 pb;

    /* l2cap format
       u16  length
       u16  cid
    */

    l2len = bt_read_u16(input);
    cid = bt_read_u16(input + 2);

    l2cap_printf("L2IN %x,%x\n", cid, l2len);

    if (cid == L2CAP_ATT_CID) {
        // le
        if (bt_gatt_input(input + 4, isize - 4)) {
            l2cap.outputs |= ATT_OUTPUT;
        }
    } else {
        // edr

        pb = flags & 0x3;
        //bc = flags >> 2;

        if (pb != HCI_PB_CONTINUE) {
            // first packet
            l2cap.offset = 0;
            l2cap.length = l2len;
        }

        memcpy(l2cap.buffer + l2cap.offset,
               input + 4, isize - 4);
        l2cap.offset += isize - 4;

        if (l2cap.offset == l2cap.length) {
            if (cid == L2CAP_SIG_CID) {
                if (l2cap_sig_input(input + 4, isize - 4)) {
                    l2cap.outputs |= SIG_OUTPUT;
                }
#ifdef EXPERIMENTAL
            } else if (cid == l2cap.sdp_cid) {
                if (sdp_input(input + 4, isize - 4)) {
                    l2cap.outputs |= SDP_OUTPUT;
                }
            } else if (cid == l2cap.rfcomm_cid) {
                if (rfcomm_input(input + 4, isize - 4)) {
                    l2cap.outputs |= RFCOMM_OUTPUT;
                }
#endif // EXPERIMENTAL
            } else if (cid == l2cap.vport_cid) {
                if (vport_input(input + 4, isize - 4)) {
                    l2cap.outputs |= VPORT_OUTPUT;
                }
            }
        }
    }

    return l2cap.outputs;
}

u8 l2cap_output(u8* output, u16* osize, u8* edr)
{
    u16 payload_size;

    *edr = 1;
    payload_size = *osize - 4;

    if (l2cap.outputs & ATT_OUTPUT) {
        l2cap.outputs &= ~ATT_OUTPUT;
        if (bt_gatt_output(output + 4, &payload_size)) {
            l2cap.outputs |= ATT_OUTPUT;
        }
        bt_write_u16(output, payload_size);
        bt_write_u16(output + 2, L2CAP_ATT_CID);
        *osize = payload_size + 4;
        *edr = 0;
    } else if (l2cap.outputs & SIG_OUTPUT) {
        l2cap.outputs &= ~SIG_OUTPUT;
        if (l2cap_sig_output(output + 4, &payload_size)) {
            l2cap.outputs |= SIG_OUTPUT;
        }
        bt_write_u16(output, payload_size);
        bt_write_u16(output + 2, L2CAP_SIG_CID);
        *osize = payload_size + 4;
        *edr = 1;
#ifdef EXPERIMENTAL
    } else if (l2cap.outputs & SDP_OUTPUT) {
        l2cap.outputs &= ~SDP_OUTPUT;
        if (sdp_output(output + 4, &payload_size)) {
            l2cap.outputs |= SDP_OUTPUT;
        }
        bt_write_u16(output, payload_size);
        bt_write_u16(output + 2, l2cap.sdp_cid);
        *osize = payload_size + 4;
        *edr = 1;
    } else if (l2cap.outputs & RFCOMM_OUTPUT) {
        l2cap.outputs &= ~RFCOMM_OUTPUT;
        if (rfcomm_output(output + 4, &payload_size)) {
            l2cap.outputs |= RFCOMM_OUTPUT;
        }
        bt_write_u16(output, payload_size);
        bt_write_u16(output + 2, l2cap.rfcomm_cid);
        *osize = payload_size + 4;
        *edr = 1;
#endif // EXPERIMENTAL
    } else if (l2cap.outputs & VPORT_OUTPUT) {
        l2cap.outputs &= ~VPORT_OUTPUT;
        if (vport_output(output + 4, &payload_size)) {
            l2cap.outputs |= VPORT_OUTPUT;
        }
        bt_write_u16(output, payload_size);
        bt_write_u16(output + 2, l2cap.vport_cid);
        *osize = payload_size + 4;
        *edr = 1;
    } else {
        *osize = 0;
    }

    return l2cap.outputs;
}

static u8 l2cap_sig_input(u8* input, u16 isize)
{
    u8 has_output = 0;

    l2cap.request.code = input[0];
    l2cap.request.id = input[1];

    l2cap_printf("L2SIG-IN: 0x%x\n", l2cap.request.code);

    switch (l2cap.request.code) {
    case L2CAP_COMMAND_REJECT:
        break;
    case L2CAP_CONNECTION_REQUEST:
        l2cap.request.u.connection.psm = bt_read_u16(input + 4);
        l2cap.request.u.connection.scid = bt_read_u16(input + 6);
        has_output = 1;
        break;
    case L2CAP_CONNECTION_RESPONSE:
        break;
    case L2CAP_CONFIGURE_REQUEST:
        l2cap.request.u.configure.dcid = bt_read_u16(input + 4);
        has_output = 1;
        break;
    case L2CAP_CONFIGURE_RESPONSE:
        break;
    case L2CAP_DISCONNECTION_REQUEST:
        l2cap.request.u.disconnection.dcid = bt_read_u16(input + 4);
        l2cap.request.u.disconnection.scid = bt_read_u16(input + 6);
        has_output = 1;
        break;
    case L2CAP_DISCONNECTION_RESPONSE:
        break;
    case L2CAP_INFORMATION_REQUEST:
        l2cap.request.u.info.type = bt_read_u16(input + 4);
        has_output = 1;
        break;
    }

    return has_output;
}

static u8 l2cap_sig_output(u8* output, u16* osize)
{
    u8 has_output = 0;
    u16 result;

    l2cap_printf("L2SIG-OUT: 0x%x\n", l2cap.request.code);

    *osize = 0;

    switch (l2cap.request.code) {
    case L2CAP_CONNECTION_REQUEST:
        switch (l2cap.request.u.connection.psm) {
#ifdef EXPERIMENTAL
        case L2CAP_SDP_PSM:
            l2cap.sdp_cid = l2cap.request.u.connection.scid;
            result = L2CAP_CONNECTION_SUCCESSFUL;
            break;
        case L2CAP_RFCOMM_PSM:
            l2cap.rfcomm_cid = l2cap.request.u.connection.scid;
            result = L2CAP_CONNECTION_SUCCESSFUL;
            break;
#endif // EXPERIMENTAL
        case CFG_L2CAP_VPORT_PSM:
            l2cap.vport_cid = l2cap.request.u.connection.scid;
            result = L2CAP_CONNECTION_SUCCESSFUL;
            break;
        default:
            result = L2CAP_PSM_NOT_SUPPORTED;
        }

        output[0] = L2CAP_CONNECTION_RESPONSE;
        output[1] = l2cap.request.id;
        bt_write_u16(output + 2, 8);
        bt_write_u16(output + 4, l2cap.request.u.connection.scid);
        bt_write_u16(output + 6, l2cap.request.u.connection.scid);
        bt_write_u16(output + 8, result);
        bt_write_u16(output + 10, 0);
        *osize = 12;
        break;
    case L2CAP_CONFIGURE_REQUEST:
        output[0] = L2CAP_CONFIGURE_RESPONSE;
        output[1] = l2cap.request.id;
        bt_write_u16(output + 2, 8);
        bt_write_u16(output + 4, l2cap.request.u.configure.dcid);
        bt_write_u16(output + 6, 0);
        bt_write_u16(output + 8, 0);
        output[10] = 1;
        output[11] = 2;
        bt_write_u16(output + 12, CFG_L2CAP_MTU_EDR);
        *osize = 14;

        l2cap.request.code = INTERNAL_SENDCFG_REQUEST;
        has_output = 1;
        break;
    case L2CAP_DISCONNECTION_REQUEST:
        output[0] = L2CAP_CONFIGURE_RESPONSE;
        output[1] = l2cap.request.id;
        bt_write_u16(output + 2, 4);
        bt_write_u16(output + 4, l2cap.request.u.disconnection.dcid);
        bt_write_u16(output + 6, l2cap.request.u.disconnection.scid);
        *osize = 8;
        break;
    case L2CAP_INFORMATION_REQUEST:
        output[0] = L2CAP_INFORMATION_RESPONSE;
        output[1] = l2cap.request.id;
        bt_write_u16(output + 2, 4);
        bt_write_u16(output + 4, l2cap.request.u.info.type);
        bt_write_u16(output + 6, 1);
        *osize = 8;
        break;

    case INTERNAL_SENDCFG_REQUEST:
        output[0] = L2CAP_CONFIGURE_REQUEST;
        output[1] = l2cap.request.id;
        bt_write_u16(output + 2, 8);
        bt_write_u16(output + 4, l2cap.request.u.configure.dcid);
        bt_write_u16(output + 6, 0);
        output[8] = 1;
        output[9] = 2;
        bt_write_u16(output + 10, CFG_L2CAP_MTU_EDR);
        *osize = 12;
    }

    return has_output;
}
