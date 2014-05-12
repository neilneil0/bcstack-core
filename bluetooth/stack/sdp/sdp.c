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

static struct {
    struct {
        u8 id;
        u8 tid;
    } pdu;

    union {
        struct {
            u16 uuid;
        } search;

        struct {
        } attr;

        struct {
        } search_attr;
    } u;
} sdp;

static void read_data_element(u8**input, u8* type, u32* length, u8** data);

extern const sdp_record_t spp_record;

static const sdp_record_t* records[] = {
    &spp_record,
};

u8 sdp_input(u8* input, u16 isize)
{
    u8 has_output = 0;
    u8 *p, *data;
    u8 type;
    u32 length;

    sdp.pdu.id = input[0];
    sdp.pdu.tid = bt_read_u16(input + 1);

    switch (sdp.pdu.id) {
    case SDP_ERROR_RESPONSE:
        break;
    case SDP_SERVICE_SEARCH_REQUEST:
        p = input;
        // read data element sequence
        read_data_element(&p, &type, &length, &data);
        // read UUID
        read_data_element(&p, &type, &length, &data);
        sdp.u.search.uuid = bt_read_u16(data);
        has_output = 1;
        break;
    case SDP_SERVICE_ATTRIBUTE_REQUEST:
        has_output = 1;
        break;
    case SDP_SERVICE_SEARCH_ATTRIBUTE_REQUEST:
        has_output = 1;
        break;
    }
}

u8 sdp_output(u8* output, u16* osize)
{
    switch (sdp.pdu.id) {
    case SDP_SERVICE_SEARCH_REQUEST:
        output[0] = SDP_SERVICE_SEARCH_RESPONSE;
        bt_write_u16(output + 1, sdp.pdu.tid);
        bt_write_u16(output + 3, 7); // length
        bt_write_u16(output + 5, 1); // total record count
        bt_write_u16(output + 7, 1); // current record count
        bt_write_u32(output + 9, 1); // record handle
        output[13] = 0;
        *osize = 10;
        break;
    case SDP_SERVICE_ATTRIBUTE_REQUEST:
        output[0] = SDP_SERVICE_ATTRIBUTE_RESPONSE;
        bt_write_u16(output + 1, sdp.pdu.tid);
        bt_write_u16(output + 3, 0); // length
        bt_write_u16(output + 5, 0); // attribute list byte count
        // attribute list
        output[7] = (SDP_DE_DES << 3) + SDP_DE_SIZE_VAR_8;
        output[8] = 0; // length of attr id/value pair
        output[9] = (SDP_DE_UINT << 3) + SDP_DE_SIZE_16;
        //bt_write_u16(output + 10, attr_id);
        // attr value
        // continuation
        break;
    case SDP_SERVICE_SEARCH_ATTRIBUTE_REQUEST:
        output[0] = SDP_SERVICE_SEARCH_ATTRIBUTE_RESPONSE;
        bt_write_u16(output + 1, sdp.pdu.tid);
        bt_write_u16(output + 3, 0); // length
        bt_write_u16(output + 3, 0); // attr list byte count
        // atribute list
        output[7] = (SDP_DE_DES << 3) + SDP_DE_SIZE_VAR_8;
        output[8] = 0; // length of attr id/value pair
        output[] = (SDP_DE_UINT << 3) | SDP_DE_SIZE_16;
        bt_write_u16(output + 0, attr_id);
        memcpy(output,
               records[handle - 1]->attrs[attr_index].attr_value,
               records[handle - 1]->attrs[attr_index].attr_length);
        break;
    }

    return 0;
}

static void read_data_element(u8**input, u8* type, u32* length, u8** data)
{
    u8* p = *input;
    u8 hdrlen;

    *type = p[0] >> 3;
    hdrlen = 1;
    switch (p[0] & 7) {
    case SDP_DE_SIZE_8:
        *length = 1;
        break;
    case SDP_DE_SIZE_16:
        *length = 2;
        break;
    case SDP_DE_SIZE_32:
        *length = 4;
        break;
    case SDP_DE_SIZE_64:
        *length = 8;
        break;
    case SDP_DE_SIZE_128:
        *length = 16;
        break;
    case SDP_DE_SIZE_VAR_8:
        *length = p[1];
        hdrlen += 1;
        break;
    case SDP_DE_SIZE_VAR_16:
        *length = bt_read_u16(p + 1);
        hdrlen += 2;
        break;
    case SDP_DE_SIZE_VAR_32:
        *length = bt_read_u32(p + 1);
        hdrlen += 4;
        break;
    }

    *data = *input + hdrlen;
    *input += hdrlen + *length;
}
