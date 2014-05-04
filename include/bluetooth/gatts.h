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

#ifndef _GATTS_H_
#define _GATTS_H_

#define ATT_MTU 23

typedef struct _bt_attr_t {
    u32 type; //internal representation of UUID
    u8  permission;
    u8 group_len;
} bt_attr_t;

typedef struct _bt_gatt_service_t {
    const bt_attr_t* attrs;
    u8 attr_count;
    void (*read)(u16 handle, u8* buffer, u16* size, u16 offset);
    void (*write)(u16 handle, u8* buffer, u16 size);
} bt_gatt_service_t;

#define BT_NUM_ATTRS(table) (sizeof(table) / sizeof(bt_attr_t))

void bt_gatts_print(void);
void bt_gatts_handle_request(u8* req, u16 reqlen, u8* rsp, u16* rsplen);
u8 bt_gatts_write(u16 handle, u8* value, u8 vlen);

#endif // _GATTS_H_
