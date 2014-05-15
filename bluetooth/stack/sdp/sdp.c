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

#ifdef EXPERIMENTAL

static struct {
    struct {
        u8 id;
        u8 tid;
    } pdu;

    u8 handle;
    u8 attr_idx;
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
    sdp.pdu.tid = sdp_read_u16(input + 1);

    switch (sdp.pdu.id) {
    case SDP_ERROR_RESPONSE:
        break;
    case SDP_SERVICE_SEARCH_REQUEST:
        p = input;
        // read data element sequence
        read_data_element(&p, &type, &length, &data);
        // read UUID
        read_data_element(&p, &type, &length, &data);
        //uuid = sdp_read_u16(data);
        has_output = 1;
        break;
    case SDP_SERVICE_ATTRIBUTE_REQUEST:
        has_output = 1;
        break;
    case SDP_SERVICE_SEARCH_ATTRIBUTE_REQUEST:
        sdp.handle = 1;
        sdp.attr_idx = 0;
        has_output = 1;
        break;
    }
}

u8 sdp_output(u8* output, u16* osize)
{
    const sdp_record_t* record;
    const sdp_attr_t* attr;
    u8 i;
    u8 offset;

    record = records[sdp.handle - 1];

    switch (sdp.pdu.id) {
    case SDP_SERVICE_SEARCH_REQUEST:
        output[0] = SDP_SERVICE_SEARCH_RESPONSE;
        sdp_write_u16(output + 1, sdp.pdu.tid);
        sdp_write_u16(output + 3, 7); // length
        sdp_write_u16(output + 5, 1); // total record count
        sdp_write_u16(output + 7, 1); // current record count
        sdp_write_u32(output + 9, 1); // record handle
        output[13] = 0;
        *osize = 10;
        break;
    case SDP_SERVICE_ATTRIBUTE_REQUEST:
        output[0] = SDP_SERVICE_ATTRIBUTE_RESPONSE;
        sdp_write_u16(output + 1, sdp.pdu.tid);
        sdp_write_u16(output + 3, 0); // length
        sdp_write_u16(output + 5, 0); // attribute list byte count
        // attribute list
        output[7] = (SDP_DE_DES << 3) + SDP_DE_SIZE_VAR_8;
        output[8] = 0; // length of attr id/value pair
        output[9] = (SDP_DE_UINT << 3) + SDP_DE_SIZE_16;
        //sdp_write_u16(output + 10, attr_id);
        // attr value
        // continuation
        break;
    case SDP_SERVICE_SEARCH_ATTRIBUTE_REQUEST:
        printf("attr: %x,%x\n", attr->id, attr->length);
        output[0] = SDP_SERVICE_SEARCH_ATTRIBUTE_RESPONSE;
        sdp_write_u16(output + 1, sdp.pdu.tid);

        offset = 11;

        // record handle
        output[offset++] = (SDP_DE_UINT << 3) | SDP_DE_SIZE_16;
        sdp_write_u16(output + offset, SDP_SERVICE_RECORD_HANDLE);
        offset += 2;
        output[offset++] = (SDP_DE_UINT << 3) | SDP_DE_SIZE_16;
        sdp_write_u16(output + offset, 1);
        offset += 2;

        for (i=0; i<record[0].count; i++) {
            attr = &record->attrs[i];
            output[offset++] = (SDP_DE_UINT << 3) | SDP_DE_SIZE_16;
            sdp_write_u16(output + offset, attr->id);
            offset += 2;
            memcpy(output + offset, attr->value, attr->length);
            offset += attr->length;
        }
        // continuation
        output[offset] = 0;

        // atribute list
        output[9] = (SDP_DE_DES << 3) + SDP_DE_SIZE_VAR_8;
        output[10] = offset - 11;

        // attribute lists
        output[7] = (SDP_DE_DES << 3) + SDP_DE_SIZE_VAR_8;
        output[8] = offset - 9;

        sdp_write_u16(output + 5, offset - 7); // attr list byte count
        sdp_write_u16(output + 3, offset - 4); // length

        *osize = offset + 1;
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
        *length = sdp_read_u16(p + 1);
        hdrlen += 2;
        break;
    case SDP_DE_SIZE_VAR_32:
        *length = sdp_read_u32(p + 1);
        hdrlen += 4;
        break;
    }

    *data = *input + hdrlen;
    *input += hdrlen + *length;
}

#endif // EXPERIMENTAL
