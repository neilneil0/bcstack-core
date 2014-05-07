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
    u8 level;
    u8 client_cfg;
} battery;

void battery_set_level(u8 _level)
{
    battery.level = _level;
}

static void battery_attr_read(u16 handle, u8* buffer, u16* size, u16 offset)
{
    switch (handle & 0xff) {
    case 0:
        bt_write_u16(buffer, 0x180F);
        *size = 2;
        break;
    case 1:
        buffer[0] = BT_GATT_CHAR_READ;
        bt_write_u16(buffer + 1, handle + 1);
        bt_write_u16(buffer + 3, 0x2A19);
        *size = 5;
        break;
    case 2:
        buffer[0] = battery.level;
        *size = 1;
        break;
    case 3:
        buffer[0] = battery.client_cfg;
        *size = 1;
        break;
    default:
        *size = 0;
    }
}

static void battery_attr_write(u16 handle, u8* buffer, u16 size)
{
    switch (handle & 0xF) {
    case 3:
        battery.client_cfg = buffer[0];
        break;
    }
}

static const bt_attr_t battery_service_attrs[] = {
    // battery service declaration
    { UUID_PRIMARY_SERVICE, BT_ATT_READABLE, 3 },

    // battery level declaration
    { UUID_CHAR, BT_ATT_READABLE, 2 },

    // battery level value
    { 0x2A19, BT_ATT_READABLE, 0 },

    // battery level client configuration
    { UUID_CLIENT_CHAR_CFG, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },
};

const bt_gatt_service_t bt_battery_service = {
    battery_service_attrs,
    BT_NUM_ATTRS(battery_service_attrs),
    battery_attr_read,
    battery_attr_write,
};
