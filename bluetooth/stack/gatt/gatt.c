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

extern const bt_gatt_service_t bt_led_service;

static const bt_gatt_service_t null_service = {
    NULL,
    0,
    NULL,
    NULL,
};

static const bt_gatt_service_t *services[] = {
    &null_service,
    &bt_battery_service,
    &bt_accel_service,
    &bt_blood_pressure_service,
    &bt_devinfo_service,
    &bt_led_service,
};
static const u8 services_num = sizeof(services)/sizeof(bt_gatt_service_t*);

#define BT_GATT_MATCH_TYPE       0x0001
#define BT_GATT_MATCH_VALUE      0x0002
#define BT_GATT_PRINT_ATTR       0x0004
#define BT_GATT_WRITE_HANDLE     0x0010
#define BT_GATT_WRITE_TYPE       0x0020
#define BT_GATT_WRITE_GROUPEND   0x0040
#define BT_GATT_WRITE_VALUE      0x0080
#define BT_GATT_WRITE_FORMAT     0x0100
#define BT_GATT_WRITE_LENGTH     0x0200

static struct {
    u8  cmtu;
    u8  reqcode;
    u16 start_handle;
    u16 end_handle;
    u16 type;
    u16 service_type;
    u16 offset;
    u8  errcode;
} gatt;

static u8 bt_gatt_find(u16 start_handle, u16 end_handle,
                       u32 type, u8* value, u8 vlen,
                       u16 flags,
                       u8* buffer, u16* size);
static u8 bt_gatt_read_blob(u16 handle, u8* buffer, u16* size, u8 offset);
static u8 bt_gatt_read_multi(u16* handles, u8 handle_count,
                             u8* buffer, u16* size);
static u8 bt_gatt_write(u16 handle, u8* value, u8 vlen);

u8 bt_gatt_input(u8* input, u16 isize)
{
    gatt.reqcode = input[0];
    gatt.errcode = 0;

    switch (gatt.reqcode) {
    case EXCH_MTU_REQ:
        gatt.cmtu = bt_read_u16(input + 1);
        break;
    case FIND_INF_REQ:
        gatt.start_handle = bt_read_u16(input + 1);
        gatt.end_handle = bt_read_u16(input + 3);
        break;
    case FIND_BY_TYPE_VAL_REQ:
        gatt.start_handle = bt_read_u16(input + 1);
        gatt.end_handle = bt_read_u16(input + 3);
        gatt.type = bt_read_u16(input + 5);
        gatt.service_type = bt_read_u16(input + 7);
        break;
    case READ_BY_TYPE_REQ:
        gatt.start_handle = bt_read_u16(input + 1);
        gatt.end_handle = bt_read_u16(input + 3);
        gatt.type = bt_read_u16(input + 5);
        break;
    case READ_REQ:
        gatt.start_handle = bt_read_u16(input + 1);
        break;
    case READ_BLOB_REQ:
        gatt.start_handle = bt_read_u16(input + 1);
        gatt.offset = bt_read_u16(input + 3);
        break;
    case READ_BY_GRP_TYPE_REQ:
        gatt.start_handle = bt_read_u16(input + 1);
        gatt.end_handle = bt_read_u16(input + 3);
        gatt.type = bt_read_u16(input + 5);
        break;
    case WRITE_REQ:
        gatt.errcode = bt_gatt_write(gatt.start_handle, input + 3, isize - 3);
        break;
    case WRITE_CMD:
        gatt.errcode = bt_gatt_write(gatt.start_handle, input + 3, isize - 3);
        break;
    case SIGN_WRITE_CMD:
        gatt.errcode = bt_gatt_write(gatt.start_handle, input + 3, isize - 15);
        break;
    default:
        gatt.errcode = REQ_NOT_SUPPORTED;
    }

    if ((gatt.reqcode == WRITE_CMD) ||
        (gatt.reqcode == SIGN_WRITE_CMD)) {
        return 0;
    } else {
        return 1;
    }
}

u8 bt_gatt_output(u8* output, u16* osize)
{
    u8 rspcode;
    u8* rsparam;
    u16 rsparamlen;

    rsparam = output + 1;
    rsparamlen = *osize - 1;

    switch (gatt.reqcode) {
    case EXCH_MTU_REQ:
        rspcode = EXCH_MTU_RSP;
        bt_write_u16(rsparam, ATT_MTU);
        rsparamlen = 2;
        break;
    case FIND_INF_REQ:
        rspcode = FIND_INF_RSP;
        gatt.errcode = bt_gatt_find(gatt.start_handle, gatt.end_handle, 0, 0, 0,
                                    BT_GATT_WRITE_HANDLE | BT_GATT_WRITE_TYPE |
                                    BT_GATT_WRITE_FORMAT,
                                    rsparam, &rsparamlen);
        break;
    case FIND_BY_TYPE_VAL_REQ:
    {
        u8 value[2];

        bt_write_u16(value, gatt.service_type);

        rspcode = FIND_BY_TYPE_VAL_RSP;
        gatt.errcode = bt_gatt_find(gatt.start_handle, gatt.end_handle,
                                    gatt.type, value, 2,
                                    BT_GATT_MATCH_TYPE | BT_GATT_MATCH_VALUE |
                                    BT_GATT_WRITE_HANDLE | BT_GATT_WRITE_GROUPEND,
                                    rsparam, &rsparamlen);
    }
    break;
    case READ_BY_TYPE_REQ:
        rspcode = READ_BY_TYPE_RSP;
        gatt.errcode = bt_gatt_find(gatt.start_handle, gatt.end_handle,
                                    gatt.type, 0, 0,
                                    BT_GATT_MATCH_TYPE |
                                    BT_GATT_WRITE_HANDLE | BT_GATT_WRITE_VALUE |
                                    BT_GATT_WRITE_LENGTH,
                                    rsparam, &rsparamlen);
        break;
    case READ_REQ:
        rspcode = READ_RSP;
        gatt.errcode = bt_gatt_read_blob(gatt.start_handle, rsparam, &rsparamlen, 0);
        break;
    case READ_BLOB_REQ:
        rspcode = READ_BLOB_RSP;
        gatt.errcode = bt_gatt_read_blob(gatt.start_handle, rsparam,
                                         &rsparamlen, gatt.offset);
        break;
    case READ_BY_GRP_TYPE_REQ:
        rspcode = READ_BY_GRP_TYPE_RSP;
        gatt.errcode = bt_gatt_find(gatt.start_handle, gatt.end_handle,
                                    gatt.type, 0, 0,
                                    BT_GATT_MATCH_TYPE |
                                    BT_GATT_WRITE_HANDLE |
                                    BT_GATT_WRITE_GROUPEND |
                                    BT_GATT_WRITE_VALUE |
                                    BT_GATT_WRITE_LENGTH,
                                    rsparam, &rsparamlen);
        break;
    case WRITE_REQ:
        rspcode = WRITE_RSP;
        rsparamlen = 0;
        break;
    }

    if (gatt.errcode == 0) {
        output[0] = rspcode;
        *osize = rsparamlen + 1;
    } else {
        output[0] = ERROR_RSP;
        output[1] = gatt.reqcode;
        bt_write_u16(output + 2, gatt.start_handle);
        output[4] = gatt.errcode;
        *osize = 5;
    }

    return 0;
}

static u8 bt_gatt_find(u16 start_handle, u16 end_handle,
                       u32 type, u8* value, u8 vlen,
                       u16 flags,
                       u8* buffer, u16* size)
{
#define BUFFERSIZE 32
    u8 i, j;
    u8 start_service = start_handle >> 8;
    u8 end_service = end_handle >> 8;
    u8 start_index, end_index;
    u16 handle;
    u8 tmpbuf[BUFFERSIZE];
    u16 tmpsize;
    u16 woffset, tmpoffset;
    u8 format;

    start_service = start_handle >> 8;
    if (start_service == 0) start_service = 1;

    end_service = end_handle >> 8;
    if (end_service >= services_num) end_service = services_num - 1;

#if GATT_VERBOSE
    printf("search attrs\n");
    printf("handle range: <%04x, %04x>\n", start_handle, end_handle);
    printf("service range: <%04x, %04x>\n", start_service, end_service);
#endif

    woffset = 0;
    for (i = start_service; i <= end_service; i++) {

        if (i == (start_handle >> 8)) {
            start_index = start_handle & 0xff;
        } else {
            start_index = 0;
        }

        if (i == (end_handle >> 8)) {
            end_index = end_handle & 0xff;
        } else {
            end_index = 0xff;
        }

        if (end_index >= services[i]->attr_count) {
            end_index = services[i]->attr_count - 1;
        }

        if (start_index > end_index) continue;

#if GATT_VERBOSE
        printf("service %02x, index range <%02x, %02x>\n",
               i, start_index, end_index);
#endif

        for (j = start_index; j <= end_index; j++) {
            handle = (i<<8) | j;
            if ((flags & BT_GATT_MATCH_TYPE) &&
                (services[i]->attrs[j].type != type)) {
                // type mismatch
                continue;
            }
            if (flags & BT_GATT_MATCH_VALUE) {
                tmpsize = BUFFERSIZE;
                services[i]->read(handle, tmpbuf, &tmpsize, 0);
                if (vlen != tmpsize) {
                    // value length mismatch
                    continue;
                }
                if (0 != memcmp(tmpbuf, value, vlen)) {
                    // value mismatch
                    continue;
                }
            }
#if GATT_VERBOSE
            if (flags & BT_GATT_PRINT_ATTR) {
                printf("    attr <%04x, %04x, %04x>",
                       handle,
                       handle + services[i]->attrs[j].group_len,
                       services[i]->attrs[j].type);
                tmpsize = BUFFERSIZE;
                services[i]->read(handle, tmpbuf, &tmpsize, 0);
                bt_dumphex(" ", tmpbuf, tmpsize);
            }
#endif
            if (woffset == 0) {
                if ((flags & BT_GATT_WRITE_FORMAT)
                    || (flags & BT_GATT_WRITE_LENGTH)) {
                    woffset = 1;
                }
            }

            tmpoffset = woffset;

            if (flags & BT_GATT_WRITE_HANDLE) {
                if (tmpoffset + 2 > *size) continue;
                bt_write_u16(buffer + tmpoffset, handle);
                tmpoffset += 2;
            }

            if (flags & BT_GATT_WRITE_TYPE) {
                if (tmpoffset + 2 > *size) continue;
                bt_write_u16(buffer + tmpoffset, services[i]->attrs[j].type);
                tmpoffset += 2;
                format = 1;
            }

            if (flags & BT_GATT_WRITE_GROUPEND) {
                if (tmpoffset + 2 > *size) continue;
                bt_write_u16(buffer + tmpoffset,
                             handle + services[i]->attrs[j].group_len);
                tmpoffset += 2;
            }

            if (flags & BT_GATT_WRITE_VALUE) {
                tmpsize = BUFFERSIZE;
                services[i]->read(handle, tmpbuf, &tmpsize, 0);
                if (tmpoffset + tmpsize > *size) continue;
                memcpy(buffer + tmpoffset, tmpbuf, tmpsize);
                tmpoffset += tmpsize;
            }

            if (woffset == 1) {
                if (flags & BT_GATT_WRITE_FORMAT) {
                    buffer[0] = format;
                } else if (flags & BT_GATT_WRITE_LENGTH) {
                    buffer[0] = tmpoffset - 1;
                }
            }

            woffset = tmpoffset;
        }
    }

    if (woffset <= 1) {
        *size = 0;
        return ATTR_NOT_FOUND;
    } else {
        *size = woffset;
        return 0;
    }
}

void bt_gatt_print()
{
    u16 size = 0;
    printf("attribute table\n");
    bt_gatt_find(1, 0xffff, 0, 0, 0,
                 BT_GATT_PRINT_ATTR,
                 0, &size);
    printf("end of table\n");
}

u8 bt_gatt_read_blob(u16 handle, u8* buffer, u16* size, u8 offset)
{
    u8 i, j;

    i = handle >> 8;
    j = handle & 0xff;

    if ((i > 0) && (i < services_num)) {
        if (j < services[i]->attr_count) {
            services[i]->read(handle, buffer, size, offset);
            return 0;
        }
    }

    return 1;
}

#if 0
u8 bt_gatt_read_multi(u16* handles, u8 handle_count, u8* buffer, u16* size)
{
    // TODO
    return 0;
}
#endif

u8 bt_gatt_write(u16 handle, u8* value, u8 vlen)
{
    u8 i, j;

    i = handle >> 8;
    j = handle & 0xff;

    if ((i > 0) && (i < services_num)) {
        if (j < services[i]->attr_count) {
            services[i]->write(handle, value, vlen);
            return 0;
        }
    }

    return 1;
}
