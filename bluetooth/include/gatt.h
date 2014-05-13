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

#ifndef _GATT_H_
#define _GATT_H_

#define ATT_MTU 23

#define LED_BASE_UUID           0xFF10
#define ACCEL_BASE_UUID         0xFFA0

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

#define GATT_WRITE_CHAR_DECL(_buffer, _handle, _uuid, _props, _size)    \
    do {                                                                \
        (_buffer)[0] = (_props);                                        \
        bt_write_u16((_buffer) + 1, (_handle) + 1);                     \
        bt_write_u16((_buffer) + 3, (_uuid));                           \
        *(_size) = 5;                                                   \
    } while(0)

void bt_gatt_print(void);
u8 bt_gatt_input(u8* input, u16 isize);
u8 bt_gatt_output(u8* output, u16* osize);

#if DEBUG_GATT
#define gatt_printf printf
#else
#define gatt_printf(...)
#endif

#endif // _GATT_H_
