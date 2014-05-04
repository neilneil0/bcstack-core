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

#include "bluetooth/host.h"

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
};
static const u8 services_num = sizeof(services)/sizeof(bt_gatt_service_t*);
static u8 client_mtu;

#define BT_GATTS_MATCH_TYPE       0x0001
#define BT_GATTS_MATCH_VALUE      0x0002
#define BT_GATTS_PRINT_ATTR       0x0004
#define BT_GATTS_WRITE_HANDLE     0x0010
#define BT_GATTS_WRITE_TYPE       0x0020
#define BT_GATTS_WRITE_GROUPEND   0x0040
#define BT_GATTS_WRITE_VALUE      0x0080
#define BT_GATTS_WRITE_FORMAT     0x0100
#define BT_GATTS_WRITE_LENGTH     0x0200

static u8 bt_gatts_find(u16 start_handle, u16 end_handle,
                        u32 type, u8* value, u8 vlen,
                        u16 flags,
                        u8* buffer, u16* size);
static u8 bt_gatts_read_blob(u16 handle, u8* buffer, u16* size, u8 offset);
static u8 bt_gatts_read_multi(u16* handles, u8 handle_count,
                      u8* buffer, u16* size);

void bt_gatts_handle_request(u8* req, u16 reqlen, u8* rsp, u16* rsplen)
{
    u8  reqcode, rspcode;
    u8* rsparam;
    u16 rsparamlen;
    u8  errcode = UNLIKELY_ERROR;
    u16 start_handle = 0;
    u16 end_handle;
    u16 type;
    u8* value;
    u16 vlen;
    u16 offset;

    reqcode = req[0];
    rsparam = rsp + 1;
    rsparamlen = *rsplen - 1;

    switch (reqcode) {
    case EXCH_MTU_REQ:
    {
        rspcode = EXCH_MTU_RSP;
        errcode = 0;
        client_mtu = bt_read_u16(req + 1);
        bt_write_u16(rsparam, ATT_MTU);
        rsparamlen = 2;
    }
    break;
    case FIND_INF_REQ:
    {
        start_handle = bt_read_u16(req + 1);
        end_handle = bt_read_u16(req + 3);
        rspcode = FIND_INF_RSP;
        errcode = bt_gatts_find(start_handle, end_handle, 0, 0, 0,
                                BT_GATTS_WRITE_HANDLE | BT_GATTS_WRITE_TYPE |
                                BT_GATTS_WRITE_FORMAT,
                                rsparam, &rsparamlen);
    }
    break;
    case FIND_BY_TYPE_VAL_REQ:
    {
        start_handle = bt_read_u16(req + 1);
        end_handle = bt_read_u16(req + 3);
        type = bt_read_u16(req + 5);
        value = req + 7;
        vlen = reqlen - 7;

        rspcode = FIND_BY_TYPE_VAL_RSP;
        errcode = bt_gatts_find(start_handle, end_handle, type, value, vlen,
                                BT_GATTS_MATCH_TYPE | BT_GATTS_MATCH_VALUE |
                                BT_GATTS_WRITE_HANDLE | BT_GATTS_WRITE_GROUPEND,
                                rsparam, &rsparamlen);
    }
    break;
    case READ_BY_TYPE_REQ:
    {
        start_handle = bt_read_u16(req + 1);
        end_handle = bt_read_u16(req + 3);
        type = bt_read_u16(req + 5);

        rspcode = READ_BY_TYPE_RSP;
        errcode = bt_gatts_find(start_handle, end_handle, type, 0, 0,
                                BT_GATTS_MATCH_TYPE |
                                BT_GATTS_WRITE_HANDLE | BT_GATTS_WRITE_VALUE |
                                BT_GATTS_WRITE_LENGTH,
                                rsparam, &rsparamlen);

    }
    break;
    case READ_REQ:
    {
        start_handle = bt_read_u16(req + 1);

        rspcode = READ_RSP;
        errcode = bt_gatts_read_blob(start_handle, rsparam, &rsparamlen, 0);
    }
    break;
    case READ_BLOB_REQ:
    {
        start_handle = bt_read_u16(req + 1);
        offset = bt_read_u16(req + 3);

        rspcode = READ_BLOB_RSP;
        errcode = bt_gatts_read_blob(start_handle, rsparam, &rsparamlen, offset);
    }
    break;
    case READ_BY_GRP_TYPE_REQ:
    {
        start_handle = bt_read_u16(req + 1);
        end_handle = bt_read_u16(req + 3);
        type = bt_read_u16(req + 5);

        rspcode = READ_BY_GRP_TYPE_RSP;
        errcode = bt_gatts_find(start_handle, end_handle, type, 0, 0,
                                BT_GATTS_MATCH_TYPE |
                                BT_GATTS_WRITE_HANDLE |
                                BT_GATTS_WRITE_GROUPEND |
                                BT_GATTS_WRITE_VALUE |
                                BT_GATTS_WRITE_LENGTH,
                                rsparam, &rsparamlen);

    }
    break;
    case WRITE_REQ:
    {
        start_handle = bt_read_u16(req + 1);
        value = req + 3;
        vlen = reqlen - 3;

        rspcode = WRITE_RSP;
        rsparamlen = 0;
        errcode = bt_gatts_write(start_handle, value, vlen);
    }
    break;
    default:
        errcode = REQ_NOT_SUPPORTED;
    }

    if (errcode == 0) {
        rsp[0] = rspcode;
        *rsplen = rsparamlen + 1;
    } else {
        rsp[0] = ERROR_RSP;
        rsp[1] = reqcode;
        bt_write_u16(rsp + 2, start_handle);
        rsp[4] = errcode;
        *rsplen = 5;
    }
}

static u8 bt_gatts_find(u16 start_handle, u16 end_handle,
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

#if DEBUG
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

#if DEBUG
        printf("service %02x, index range <%02x, %02x>\n",
               i, start_index, end_index);
#endif

        for (j = start_index; j <= end_index; j++) {
            handle = (i<<8) | j;
            if ((flags & BT_GATTS_MATCH_TYPE) &&
                (services[i]->attrs[j].type != type)) {
                // type mismatch
                continue;
            }
            if (flags & BT_GATTS_MATCH_VALUE) {
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
#if DEBUG
            if (flags & BT_GATTS_PRINT_ATTR) {
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
                if ((flags & BT_GATTS_WRITE_FORMAT)
                    || (flags & BT_GATTS_WRITE_LENGTH)) {
                    woffset = 1;
                }
            }

            tmpoffset = woffset;

            if (flags & BT_GATTS_WRITE_HANDLE) {
                if (tmpoffset + 2 > *size) continue;
                bt_write_u16(buffer + tmpoffset, handle);
                tmpoffset += 2;
            }

            if (flags & BT_GATTS_WRITE_TYPE) {
                if (tmpoffset + 2 > *size) continue;
                bt_write_u16(buffer + tmpoffset, services[i]->attrs[j].type);
                tmpoffset += 2;
                format = 1;
            }

            if (flags & BT_GATTS_WRITE_GROUPEND) {
                if (tmpoffset + 2 > *size) continue;
                bt_write_u16(buffer + tmpoffset,
                             handle + services[i]->attrs[j].group_len);
                tmpoffset += 2;
            }

            if (flags & BT_GATTS_WRITE_VALUE) {
                tmpsize = BUFFERSIZE;
                services[i]->read(handle, tmpbuf, &tmpsize, 0);
                if (tmpoffset + tmpsize > *size) continue;
                memcpy(buffer + tmpoffset, tmpbuf, tmpsize);
                tmpoffset += tmpsize;
            }

            if (woffset == 1) {
                if (flags & BT_GATTS_WRITE_FORMAT) {
                    buffer[0] = format;
                } else if (flags & BT_GATTS_WRITE_LENGTH) {
                    buffer[0] = tmpoffset - 1;
                }
            }

            woffset = tmpoffset;
        }
    }

end:
    if (woffset <= 1) {
        *size = 0;
        return ATTR_NOT_FOUND;
    } else {
        *size = woffset;
        return 0;
    }
}

void bt_gatts_print()
{
    u16 size = 0;
    printf("attribute table\n");
    bt_gatts_find(1, 0xffff, 0, 0, 0,
                  BT_GATTS_PRINT_ATTR,
                  0, &size);
    printf("end of table\n");
}

u8 bt_gatts_read_blob(u16 handle, u8* buffer, u16* size, u8 offset)
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

u8 bt_gatts_read_multi(u16* handles, u8 handle_count, u8* buffer, u16* size)
{
    // TODO
    return 0;
}

u8 bt_gatts_write(u16 handle, u8* value, u8 vlen)
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
