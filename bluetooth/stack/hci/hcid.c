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

/*
 * HCI Local Data
 */
static struct {
    const u8* curr_reset_cmd;
    u8 ncmds; // number of commands that can be sent

    struct {
        u16 hconn;
    } le;

#if !DISABLE_BT_CLASSICAL
    struct {
        u16 hconn;
        u8  bdaddr[6];
    } edr;
#endif

    struct {
        u8 visible : 1;
    } state;

    struct {
        u8 reset : 1;
        u8 set_adv_params : 1;
        u8 set_adv_data : 1;
        u8 set_adv_en : 1;
#if !DISABLE_BT_CLASSICAL
        u8 write_local_name : 1;
        u8 write_eir : 1;
        u8 write_scan_en : 1;
        u8 accept_conn : 1;
        u8 io_cap_reply : 1;
        u8 user_cfm_reply : 1;
#endif
    } tasks;
} hci;

static void hci_send_command(u8* buffer, u16 size);
static void hci_event_received(u8* data, u16 len);
#if !DISABLE_BT_CLASSICAL
static void hci_conn_cmplt( u8* data, u8 len );
static void hci_conn_req( u8* data, u8 len );
#endif
static void hci_disconn_cmplt( u8* data, u8 len );
static void hci_cmd_cmplt( u8* data, u8 len );
static void hci_cmd_status( u8* data, u8 len );
static void hci_num_of_cmplt_pkts( u8* data, u8 len );
static void hci_hw_err( u8* data, u8 len );
#if !DISABLE_BT_CLASSICAL
static void hci_io_cap_req( u8* data, u8 len );
static void hci_io_cap_rsp( u8* data, u8 len );
static void hci_user_cfm_req( u8* data, u8 len );
static void hci_simple_pair_cmplt( u8* data, u8 len );
#endif
static void hci_le_conn_cmplt( u8* data, u8 len );
static void hci_le_adv_report( u8* data, u8 len );
static void hci_le_conn_update( u8* data, u8 len );
static void hci_le_long_term_key_req( u8* data, u8 len );
static void hci_acl_received(u8* data, u16 len);
static void hci_send_acl(u8* buffer, u16 size);

#if DEBUG_HCI
#define hci_printf printf
#define hci_dumphex bt_dumphex
#else
#define hci_printf(...)
#define hci_dumphex(...)
#endif

// HCI Reset Sequence
static const u8 hci_reset_seq[] = {
    0x03, 0x0C, 0x00, // reset
    0x03, 0x10, 0x00, // read local supported features
    0x01, 0x10, 0x00, // read local version
    0x09, 0x10, 0x00, // read BD ADDR
    0x05, 0x10, 0x00, // read buffer size
#if !DISABLE_BT_CLASSICAL
    0x23, 0x0C, 0x00, // read class of device
    0x25, 0x0C, 0x00, // read voice setting
#endif
    0x05, 0x0C, 0x01, 0x00, // set event filter (clear all)
    0x16, 0x0C, 0x02, 0x00, 0x7D, // write connection accept timeout (32000)
#if !DISABLE_BT_CLASSICAL
    0x1B, 0x0C, 0x00, // read page scan activity
    0x46, 0x0C, 0x00, // read page scan type
#endif
    0x02, 0x20, 0x00, // le read buffer size
    0x03, 0x20, 0x00, // le read local supported features
    0x07, 0x20, 0x00, // le read advertising channel tx power
    0x0F, 0x20, 0x00, // le read white list size
    0x1C, 0x20, 0x00, // le read supported states
    0x01, 0x0C, 0x08, 0xFF, 0xFF, 0xFB, 0xFF, 0x07, 0xF8, 0xBF, 0x3D, // set event mask
    0x01, 0x20, 0x08, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // le set event mask
#if !DISABLE_BT_CLASSICAL
    0x56, 0x0C, 0x01, 0x01, // write simple pairing mode (1)
    0x45, 0x0C, 0x01, 0x02, // write inquiry mode (2)
    0x58, 0x0C, 0x00, // read inquiry response tx power
#endif
    0x04, 0x10, 0x01, 0x01, // read local extended features (page 1)
#if !DISABLE_BT_CLASSICAL
    0x12, 0x0C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // delete stored key
    0x0F, 0x08, 0x02, 0x0F, 0x00, // write default link policy settings
#endif
    0x6D, 0x0C, 0x02, 0x01, 0x01, // write le host supported (1)
#if !DISABLE_BT_CLASSICAL
    0x1C, 0x0C, 0x04, 0x00, 0x20, 0x12, 0x00, // write page scan activity
    0x1E, 0x0C, 0x04, 0x00, 0x20, 0x12, 0x00, // write inquiry scan activity
#endif
    0,0,0 // end of sequence
};

void hci_handle_transport_event(u8 channel, u8* buffer, u16 size)
{
    switch (channel) {
	case BT_COMMAND_CHANNEL:
        hci_send_command(buffer, size);
        break;
	case BT_EVENT_CHANNEL:
        hci_event_received(buffer, size);
        break;
	case BT_ACL_IN_CHANNEL:
        hci_acl_received(buffer, size);
        break;
	case BT_ACL_OUT_CHANNEL:
        hci_send_acl(buffer, size);
        break;
    }
}

static void hci_send_command(u8* buffer, u16 size)
{
    u8 cmdlen;
    u8 send_cmd = 0;

    if (hci.ncmds) {
        if (hci.tasks.reset) {
            cmdlen = hci.curr_reset_cmd[2] + 3;
            memcpy(buffer, hci.curr_reset_cmd, cmdlen);

            hci.curr_reset_cmd += cmdlen;
            send_cmd = 1;

            if ((hci.curr_reset_cmd[0] == 0) &&
                (hci.curr_reset_cmd[1] == 0)) {
                hci_printf("radio initialized\n");
                hci.tasks.reset = 0;
            }
        } else if (hci.tasks.set_adv_params) {
            static const u8 le_set_adv_params[] = {
                6,0x20,	// set adv params
                0xF, // params len
                0x20,0, // min int
                0x20,0, // max int
                0, // adv type
                0, // own addr type
                0, //direct addr type
                0,0,0,0,0,0, //direct addr
                7, // channel map
                0  // filter
            };
            hci.tasks.set_adv_params = 0;

            memcpy(buffer, le_set_adv_params, sizeof(le_set_adv_params));
            send_cmd = 1;
        } else if (hci.tasks.set_adv_data) {
            hci.tasks.set_adv_data = 0;

            buffer[0] = 8;
            buffer[1] = 0x20;
            buffer[2] = 32;
            memset(buffer + 3, 0, 32);

            buffer[3] = sizeof(CFG_DEVICE_NAME) + 3; // adv data len
            buffer[4] = sizeof(CFG_DEVICE_NAME) + 2; // adv element len
            buffer[5] = 9; // type: complete name
            memcpy(buffer + 6, CFG_DEVICE_NAME, sizeof(CFG_DEVICE_NAME));

            send_cmd = 1;
        } else if (hci.tasks.set_adv_en) {
            static const u8 le_set_adv_en[] = {0xA, 0x20, 1, 1};

            hci.tasks.set_adv_en = 0;

            memcpy(buffer, le_set_adv_en, sizeof(le_set_adv_en));

            if ((hci.le.hconn == 0) &&
                (hci.state.visible == 1)) {
                buffer[3] = 1;
            } else {
                buffer[3] = 0;
            }
            send_cmd = 1;

            hci_printf("adv_en = %x\n", buffer[3]);
        }
#if !DISABLE_BT_CLASSICAL
        else if (hci.tasks.write_local_name) {
            hci.tasks.write_local_name = 0;

            buffer[0] = 0x13;
            buffer[1] = 0xC;
            buffer[2] = 248;

            strncpy(buffer + 3, CFG_DEVICE_NAME, 248);

            send_cmd = 1;
        } else if (hci.tasks.write_eir) {
            hci.tasks.write_eir = 0;

            buffer[0] = 0x52;
            buffer[1] = 0xC;
            buffer[2] = 241;
            buffer[3] = 1; // FEC required
            memset(buffer + 4, 0, 240);

            // EIR Element: complete local name
            buffer[4] = sizeof(CFG_DEVICE_NAME) + 1;
            buffer[5] = 9;
            memcpy(buffer + 6, CFG_DEVICE_NAME, sizeof(CFG_DEVICE_NAME));

            send_cmd = 1;
        } else if (hci.tasks.write_scan_en) {
            static const u8 hci_write_scan_en[] = {0x1A, 0xC, 1, 0};

            hci.tasks.write_scan_en = 0;

            memcpy(buffer, hci_write_scan_en, sizeof(hci_write_scan_en));

            if ((hci.edr.hconn == 0) &&
                (hci.state.visible == 1)) {
                buffer[3] = 3;
            } else {
                buffer[3] = 0;
            }
            send_cmd = 1;

            hci_printf("scan enable = %x\n", buffer[3]);
        } else if (hci.tasks.accept_conn) {
            hci.tasks.accept_conn = 0;

            buffer[0] = 9;
            buffer[1] = 4;
            buffer[2] = 7;
            memcpy(buffer + 3, hci.edr.bdaddr, 6);
            buffer[9] = 1;

            send_cmd = 1;
            hci_printf("accept conn\n");
        } else if (hci.tasks.io_cap_reply) {
            hci.tasks.io_cap_reply = 0;

            buffer[0] = 0x2B;
            buffer[1] = 4;
            buffer[2] = 9;
            memcpy(buffer + 3, hci.edr.bdaddr, 6);
            buffer[9] = 3; // No IO
            buffer[10] = 0; // No OOB data
            buffer[11] = 0;

            send_cmd = 1;
        } else if (hci.tasks.user_cfm_reply) {
            hci.tasks.user_cfm_reply = 0;

            buffer[0] = 0x2C;
            buffer[1] = 4;
            buffer[2] = 6;
            memcpy(buffer + 3, hci.edr.bdaddr, 6);

            send_cmd = 1;
        }
#endif

        if (send_cmd) {
            cmdlen = buffer[2] + 3;

            hci_dumphex("CMD", buffer, cmdlen);
            hci_write(BT_COMMAND_CHANNEL, cmdlen);

            hci.ncmds--;
        }
    }
}

static void hci_event_received(u8* data, u16 len)
{
    u8 event_code;
    u8 param_len;
    u8 subcode;
    u8 *param;

    /*
      event format
      0: event code
      1: parameter total length
      *: parameters
      */
    
    event_code = data[0];
    param_len = data[1];
    param = data + 2;

    hci_dumphex("EVT", data, len);
    
    switch (event_code) {
#if !DISABLE_BT_CLASSICAL
    case HCI_CONN_CMPLT_EVT:
        hci_conn_cmplt(param, param_len);
        break;
    case HCI_CONN_REQ_EVT:
        hci_conn_req(param, param_len);
        break;
#endif
    case HCI_DISCONN_CMPLT_EVT:
        hci_disconn_cmplt(param, param_len);
        break;
    case HCI_CMD_CMPLT_EVT:
        hci_cmd_cmplt(param, param_len);
        break;
    case HCI_CMD_STATUS_EVT:
        hci_cmd_status(param, param_len);
        break;
    case HCI_NUM_OF_CMPLT_PKTS_EVT:
        hci_num_of_cmplt_pkts(param, param_len);
        break;
    case HCI_HW_ERR_EVT:
        break;
#if !DISABLE_BT_CLASSICAL
    case HCI_IO_CAP_REQ:
        hci_io_cap_req(param, param_len);
        break;
    case HCI_IO_CAP_RSP:
        hci_io_cap_rsp(param, param_len);
        break;
    case HCI_USER_CFM_REQ:
        hci_user_cfm_req(param, param_len);
        break;
    case HCI_SIMPLE_PAIR_CMPLT:
        hci_simple_pair_cmplt(param, param_len);
        break;
#endif
    case HCI_LE_META_EVT:
        subcode = data[2];
        switch(subcode) {
        case HCI_LE_CONN_CMPLT_EVT:
            hci_le_conn_cmplt(param, param_len);
            break;
        case HCI_LE_ADV_REPORT_EVT:
            hci_le_adv_report(param, param_len);
            break;
        case HCI_LE_CONN_UPDATE_EVT:
            hci_le_conn_update(param, param_len);
            break;
        case HCI_LE_LONG_TERM_KEY_REQ_EVT:
            hci_le_long_term_key_req(param, param_len);
            break;
        }
    case 0xFF:
#if EM9301
    {
        void em_event_input( u8* data, u8 len );
        em_event_input( param, param_len );
    }
#endif
        break;
    }
}

#if !DISABLE_BT_CLASSICAL
static void hci_conn_cmplt( u8* data, u8 len )
{
    if (data[0] == 0) {
        hci_printf("edr connected\n");

        hci.edr.hconn = bt_read_u16(data + 1);

        hci.tasks.write_scan_en = 1;
        hci_write_later(BT_COMMAND_CHANNEL);
    }
}

static void hci_conn_req( u8* data, u8 len )
{
    memcpy(hci.edr.bdaddr, data, 6);

    hci.tasks.accept_conn = 1;
    hci_write_later(BT_COMMAND_CHANNEL);
}
#endif

static void hci_disconn_cmplt( u8* data, u8 len )
{
    u16 handle;

    handle = bt_read_u16(data + 1);

#if !DISABLE_BT_CLASSICAL
    if (handle == hci.edr.hconn) {
        hci_printf("edr disconnected\n");
        hci.edr.hconn = 0;
        hci.tasks.write_scan_en = 1;
    } else
#endif
        if (handle == hci.le.hconn) {
        hci_printf("le disconnected\n");
        hci.le.hconn = 0;
        hci.tasks.set_adv_en = 1;
    }

    hci_write_later(BT_COMMAND_CHANNEL);
}

static void hci_cmd_cmplt( u8* data, u8 len )
{
    hci.ncmds = data[0];

    hci_write_later(BT_COMMAND_CHANNEL);
}

static void hci_cmd_status( u8* data, u8 len )
{
    hci.ncmds = data[1];

    hci_write_later(BT_COMMAND_CHANNEL);
}

static void hci_num_of_cmplt_pkts( u8* data, u8 len )
{
    
}

static void hci_hw_err( u8* data, u8 len )
{
}


#if !DISABLE_BT_CLASSICAL
static void hci_io_cap_req( u8* data, u8 len )
{
    hci.tasks.io_cap_reply = 1;

    hci_write_later(BT_COMMAND_CHANNEL);
}

static void hci_io_cap_rsp( u8* data, u8 len )
{
}

static void hci_user_cfm_req( u8* data, u8 len )
{
    hci.tasks.user_cfm_reply = 1;

    hci_write_later(BT_COMMAND_CHANNEL);
}

static void hci_simple_pair_cmplt( u8* data, u8 len )
{
}
#endif

static void hci_le_conn_cmplt( u8* data, u8 len )
{
    hci_printf("le connected\n");

    hci.le.hconn = bt_read_u16(data + 2);
    hci.tasks.set_adv_en = 1;
    hci_write_later(BT_COMMAND_CHANNEL);
}

static void hci_le_adv_report( u8* data, u8 len )
{
    
}

static void hci_le_conn_update( u8* data, u8 len )
{
    
}

static void hci_le_long_term_key_req( u8* data, u8 len )
{
    
}

static void hci_acl_received(u8* input, u16 isize)
{
    u8 handle;
    u8 flags;

    hci_dumphex("ACLI", input, isize);

    /* acl format
       bits 0-11   handle
       bits 12-13  pb flag
       bits 14-15  bc flag
       bits 16-31  input total length
    */

    handle = bt_read_u16(input) & 0xFFF;
    flags = input[1] >> 4;
    //acl_len = bt_read_u16(input +2);

    if ((hci.le.hconn != handle)
#if !DISABLE_BT_CLASSICAL
        && (hci.edr.hconn != handle)
#endif
        ) return;

    if (l2cap_input(input + 4, isize - 4, flags)) {
        hci_write_later(BT_ACL_OUT_CHANNEL);
    }
}

static void hci_send_acl(u8* output, u16 osize)
{
    u16 payload_size;
    u8 edr;

    payload_size = osize - 4;
    l2cap_output(output + 4, &payload_size, &edr);

    if (payload_size) {
#if !DISABLE_BT_CLASSICAL
        if (edr) {
            bt_write_u16(output, hci.edr.hconn | 0x2000);
        } else
#endif
        {
            bt_write_u16(output, hci.le.hconn | 0x2000);
        }
        bt_write_u16(output + 2, payload_size);

        hci_dumphex("ACLO", output, payload_size + 4);
        hci_write(BT_ACL_OUT_CHANNEL, payload_size + 4);
    }
}

void bt_setup(void)
{
    memset(&hci, 0, sizeof(hci));
    hci.ncmds = INIT_CMD_NUM;
    hci.curr_reset_cmd = hci_reset_seq;

    hci_setup();
}

void bt_loop(void)
{
    hci_loop();
}

void bt_shutdown(void)
{
    hci_shutdown();
}

void gap_reset()
{
    hci.tasks.reset = 1;
    hci.curr_reset_cmd = hci_reset_seq;
    hci.tasks.set_adv_params = 1;
    hci.tasks.set_adv_data = 1;
#if !DISABLE_BT_CLASSICAL
    hci.tasks.write_local_name = 1;
    hci.tasks.write_eir = 1;
#endif

    hci_write_later(BT_COMMAND_CHANNEL);
}

void gap_set_visible(int v)
{
    hci.state.visible = v;
    hci.tasks.set_adv_en = 1;
#if !DISABLE_BT_CLASSICAL
    hci.tasks.write_scan_en = 1;
#endif

    hci_write_later(BT_COMMAND_CHANNEL);
}
