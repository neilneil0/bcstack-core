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
    u8 measurement_cfg;
    u8 cuff_cfg;
} blood_pressure;

#define BLOOD_PRESSURE_SERVICE_UUID         0x1810
#define BLOOD_PRESSURE_MEASUREMENT_UUID     0x2A35
#define BLOOD_PRESSURE_CUFF_UUID            0x2A36
#define BLOOD_PRESSURE_FEATURE_UUID         0x2A49

enum {
    BLOOD_PRESSURE_SERVICE_DECL = 0,

    BLOOD_PRESSURE_MEASUREMENT_DECL,
    BLOOD_PRESSURE_MEASUREMENT_VALUE,
    BLOOD_PRESSURE_MEASUREMENT_CLIENT_CFG,

    BLOOD_PRESSURE_CUFF_DECL,
    BLOOD_PRESSURE_CUFF_VALUE,
    BLOOD_PRESSURE_CUFF_CLIENT_CFG,

    BLOOD_PRESSURE_FEATURE_DECL,
    BLOOD_PRESSURE_FEATURE_VALUE,
};

static void blood_pressure_attr_read(u16 handle, u8* buffer, u16* size, u16 offset)
{
    switch (handle & 0xff) {
    case BLOOD_PRESSURE_SERVICE_DECL:
        bt_write_u16(buffer, BLOOD_PRESSURE_SERVICE_UUID);
        *size = 2;
        break;

    case BLOOD_PRESSURE_MEASUREMENT_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, BLOOD_PRESSURE_MEASUREMENT_UUID,
                             BT_GATT_CHAR_INDICATE, size);
        break;
    case BLOOD_PRESSURE_MEASUREMENT_CLIENT_CFG:
        buffer[0] = blood_pressure.measurement_cfg;
        *size = 1;
        break;

    case BLOOD_PRESSURE_CUFF_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, BLOOD_PRESSURE_CUFF_UUID,
                             BT_GATT_CHAR_NOTIFY, size);
        break;
    case BLOOD_PRESSURE_CUFF_CLIENT_CFG:
        buffer[0] = blood_pressure.cuff_cfg;
        *size = 1;
        break;

    case BLOOD_PRESSURE_FEATURE_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, BLOOD_PRESSURE_FEATURE_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case BLOOD_PRESSURE_FEATURE_VALUE:
        buffer[0] = 0;
        buffer[1] = 1;
        *size = 2;
        break;

    default:
        *size = 0;
    }
}

static void blood_pressure_attr_write(u16 handle, u8* buffer, u16 size)
{
    switch (handle & 0xff) {
    case BLOOD_PRESSURE_MEASUREMENT_CLIENT_CFG:
        blood_pressure.measurement_cfg = buffer[0];
        break;
    case BLOOD_PRESSURE_CUFF_CLIENT_CFG:
        blood_pressure.cuff_cfg = buffer[0];
        break;
    }
}

static const bt_attr_t blood_pressure_service_attrs[] = {
    // blood pressure service declaration
    { UUID_PRIMARY_SERVICE, BT_ATT_READABLE, 8 },

    // blood pressure measurement declaration
    { UUID_CHAR, BT_ATT_READABLE, 2 },
    // blood pressure measurement value
    { BLOOD_PRESSURE_MEASUREMENT_UUID, 0, 0 },
    // blood pressure measurement client configuration
    { UUID_CLIENT_CHAR_CFG, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },

    // blood pressure cuff declaration
    { UUID_CHAR, BT_ATT_READABLE, 2 },
    // blood pressure cuff value
    { BLOOD_PRESSURE_CUFF_UUID, 0, 0 },
    // blood pressure cuff client configuration
    { UUID_CLIENT_CHAR_CFG, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },

    // blood pressure feature declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // blood pressure feature value
    { BLOOD_PRESSURE_FEATURE_UUID, BT_ATT_READABLE, 0 },
};

const bt_gatt_service_t bt_blood_pressure_service = {
    blood_pressure_service_attrs,
    BT_NUM_ATTRS(blood_pressure_service_attrs),
    blood_pressure_attr_read,
    blood_pressure_attr_write,
};
