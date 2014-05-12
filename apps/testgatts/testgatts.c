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

struct {
    u16 len;
    const u8* value;
} testvec[] = {
    {3, (u8[]){EXCH_MTU_REQ , 0x20, 0}},
    {5, (u8[]){FIND_INF_REQ, 1, 0, 0xff, 0xff}},
    {5, (u8[]){FIND_INF_REQ, 0, 0x10, 0xff, 0xff}},
    {9, (u8[]){FIND_BY_TYPE_VAL_REQ, 1, 0, 0xff, 0xff, 0x00, 0x28, 0x0f, 0x18}},
    {9, (u8[]){FIND_BY_TYPE_VAL_REQ, 0, 0x11, 0xff, 0xff, 0x00, 0x28, 0x0f, 0x18}},
    {7, (u8[]){READ_BY_TYPE_REQ, 1, 0, 0xff, 0xff, 0x03, 0x28}},
    {7, (u8[]){READ_BY_TYPE_REQ, 1, 0x10, 0xff, 0xff, 0x03, 0x28}},
    {7, (u8[]){READ_BY_GRP_TYPE_REQ, 1, 0, 0xff, 0xff, 0x03, 0x28}},
    {4, (u8[]){WRITE_REQ, 0x03, 0x01, 0x03}},
    {3, (u8[]){READ_REQ, 0x03, 0x01}},
};

#define BUFFER_SIZE 32

void app_setup(void)
{
    u8 nvec = sizeof(testvec) / sizeof(testvec[0]);
    u8 buffer[BUFFER_SIZE];
    u16 size;
    u8 value[2];
    u8 retval;
    u8 i;
    u8 has_response;

    printf("test gatts\n");

    battery_set_level(0x3f);
    accel_set_xyz(0xA1, 0xA2, 0xA3);

#if DEBUG
    bt_gatt_print();
#endif

    for (i=0; i<nvec; i++) {
        printf("case %d\n", i);
        size = BUFFER_SIZE;
        bt_dumphex(" IN", testvec[i].value, testvec[i].len);
        has_response = bt_gatt_input(testvec[i].value, testvec[i].len);
        if (has_response) {
            bt_gatt_output(buffer, &size);
            bt_dumphex("OUT", buffer, size);
        } else {
            printf("OUT <>\n");
        }
    }
}

void app_loop(void)
{
    bt_exit = 1;
}

void app_shutdown(void)
{
}
