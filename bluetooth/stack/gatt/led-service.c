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
    u8 state;
} led;

#define LED_SERVICE_UUID       (LED_BASE_UUID + 0)
#define LED_STATE_UUID         (LED_BASE_UUID + 1)

enum {
    LED_SERVICE_DECL = 0,

    LED_STATE_DECL,
    LED_STATE_VALUE,
};

// this function must be provided by user of led service
extern void led_state_changed(u8 new_state);

static void led_attr_read(u16 handle, u8* buffer, u16* size, u16 offset)
{
    switch (handle & 0xff) {
    case LED_SERVICE_DECL:
        bt_write_u16(buffer, LED_SERVICE_UUID);
        *size = 2;
        break;

    case LED_STATE_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, LED_STATE_UUID,
                             BT_GATT_CHAR_READ | BT_GATT_CHAR_WRITE, size);
        break;
    case LED_STATE_VALUE:
        buffer[0] = led.state;
        *size = 1;
        break;
    }
}

static void led_attr_write(u16 handle, u8* buffer, u16 size)
{
    switch (handle & 0xF) {
    case LED_STATE_VALUE:
        led.state = buffer[0];
        led_state_changed(led.state);
        break;
    }
}

static const bt_attr_t led_service_attrs[] = {
    // led service declaration
    { UUID_PRIMARY_SERVICE, BT_ATT_READABLE, 2 },

    // led level declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },

    // led level value
    { LED_STATE_UUID, BT_ATT_READABLE, 0 },
};

const bt_gatt_service_t bt_led_service = {
    led_service_attrs,
    BT_NUM_ATTRS(led_service_attrs),
    led_attr_read,
    led_attr_write,
};
