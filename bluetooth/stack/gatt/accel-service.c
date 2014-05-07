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

#define ACCEL_SERVICE_UUID            (ACCEL_BASE_UUID + 0)
#define ACCEL_ENABLER_UUID            (ACCEL_BASE_UUID + 1)
#define ACCEL_RANGE_UUID              (ACCEL_BASE_UUID + 2)
#define ACCEL_X_UUID                  (ACCEL_BASE_UUID + 3)
#define ACCEL_Y_UUID                  (ACCEL_BASE_UUID + 4)
#define ACCEL_Z_UUID                  (ACCEL_BASE_UUID + 5)
  
#define ACCEL_RANGE_2G                20
#define ACCEL_RANGE_8G                80

enum {
    ACCEL_SERVICE_DECL = 0,

    ACCEL_ENABLER_DECL,
    ACCEL_ENABLER_VALUE,
    ACCEL_ENABLER_USER_DESCR,

    ACCEL_RANGE_DECL,
    ACCEL_RANGE_VALUE,
    ACCEL_RANGE_USER_DESCR,

    ACCEL_X_COORD_DECL,
    ACCEL_X_COORD_VALUE,
    ACCEL_X_COORD_CLIENT_CFG,
    ACCEL_X_COORD_USER_DESCR,

    ACCEL_Y_COORD_DECL,
    ACCEL_Y_COORD_VALUE,
    ACCEL_Y_COORD_CLIENT_CFG,
    ACCEL_Y_COORD_USER_DESCR,

    ACCEL_Z_COORD_DECL,
    ACCEL_Z_COORD_VALUE,
    ACCEL_Z_COORD_CLIENT_CFG,
    ACCEL_Z_COORD_USER_DESCR,
};

static struct {
    u8 enabled;
    u8 x, y, z;
    u8 xcfg, ycfg, zcfg;
    u8 xprops, yprops, zprops;
} accel;

void accel_set_xyz(u8 x, u8 y, u8 z)
{
    accel.x = x;
    accel.y = y;
    accel.z = z;
}

static void accel_attr_read(u16 handle, u8* buffer, u16* size, u16 offset)
{
    switch (handle & 0xff) {
    case ACCEL_SERVICE_DECL:
        bt_write_u16(buffer, ACCEL_SERVICE_UUID);
        *size = 2;
        break;

    case ACCEL_ENABLER_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, ACCEL_ENABLER_UUID,
                             BT_GATT_CHAR_READ | BT_GATT_CHAR_WRITE, size);
        break;
    case ACCEL_ENABLER_VALUE:
        buffer[0] = accel.enabled;
        *size = 1;
        break;
    case ACCEL_ENABLER_USER_DESCR:
        memcpy(buffer, "Accel Enable", 13);
        *size = 13;
        break;

    case ACCEL_RANGE_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, ACCEL_RANGE_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case ACCEL_RANGE_VALUE:
        buffer[0] = ACCEL_RANGE_2G;
        *size = 1;
        break;
    case ACCEL_RANGE_USER_DESCR:
        memcpy(buffer, "Accel Range", 12);
        *size = 12;
        break;

    case ACCEL_X_COORD_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, ACCEL_X_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case ACCEL_X_COORD_VALUE:
        buffer[0] = accel.x;
        *size = 1;
        break;
    case ACCEL_X_COORD_CLIENT_CFG:
        buffer[0] = accel.xcfg;
        *size = 1;
        break;
    case ACCEL_X_COORD_USER_DESCR:
        memcpy(buffer, "Accel X", 8);
        *size = 8;
        break;

    case ACCEL_Y_COORD_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, ACCEL_Y_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case ACCEL_Y_COORD_VALUE:
        buffer[0] = accel.y;
        *size = 1;
        break;
    case ACCEL_Y_COORD_CLIENT_CFG:
        buffer[0] = accel.ycfg;
        *size = 1;
        break;
    case ACCEL_Y_COORD_USER_DESCR:
        memcpy(buffer, "Accel Y", 8);
        *size = 8;
        break;

    case ACCEL_Z_COORD_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, ACCEL_Z_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case ACCEL_Z_COORD_VALUE:
        buffer[0] = accel.z;
        *size = 1;
        break;
    case ACCEL_Z_COORD_CLIENT_CFG:
        buffer[0] = accel.zcfg;
        *size = 1;
        break;
    case ACCEL_Z_COORD_USER_DESCR:
        memcpy(buffer, "Accel Z", 8);
        *size = 8;
        break;

    default:
        *size = 0;
    }
}

static void accel_attr_write(u16 handle, u8* buffer, u16 size)
{
    switch (handle & 0xF) {
    case ACCEL_ENABLER_VALUE:
        accel.enabled = buffer[0];
        break;
    case ACCEL_X_COORD_CLIENT_CFG:
        accel.xcfg = buffer[0];
        break;
    case ACCEL_Y_COORD_CLIENT_CFG:
        accel.ycfg = buffer[0];
        break;
    case ACCEL_Z_COORD_CLIENT_CFG:
        accel.zcfg = buffer[0];
        break;
    }
}

static const bt_attr_t accel_service_attrs[] = {
    // accel service declaration
    { UUID_PRIMARY_SERVICE, BT_ATT_READABLE, 18 },

    // accel enabler declaration
    { UUID_CHAR, BT_ATT_READABLE, 2 },
    // accel enabler value
    { ACCEL_ENABLER_UUID, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },
    // accel enabler user description
    { UUID_CHAR_USER_DESC, BT_ATT_READABLE, 0 },

    // accel range declaration
    { UUID_CHAR, BT_ATT_READABLE, 2 },
    // accel range value
    { ACCEL_RANGE_UUID, BT_ATT_READABLE, 0 },
    // accel range user description
    { UUID_CHAR_USER_DESC, BT_ATT_READABLE, 0 },

    // x-coordinate declaration
    { UUID_CHAR, BT_ATT_READABLE, 3 },
    // x-coordinate value
    { ACCEL_X_UUID, BT_ATT_READABLE, 0 },
    // x-coordinate client configuration
    { UUID_CLIENT_CHAR_CFG, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },
    // x-coordinate user description
    { UUID_CHAR_USER_DESC, BT_ATT_READABLE, 0 },

    // y-coordinate declaration
    { UUID_CHAR, BT_ATT_READABLE, 3 },
    // y-coordinate value
    { ACCEL_Y_UUID, BT_ATT_READABLE, 0 },
    // y-coordinate client configuration
    { UUID_CLIENT_CHAR_CFG, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },
    // y-coordinate user description
    { UUID_CHAR_USER_DESC, BT_ATT_READABLE, 0 },

    // z-coordinate declaration
    { UUID_CHAR, BT_ATT_READABLE, 3 },
    // z-coordinate value
    { ACCEL_Z_UUID, BT_ATT_READABLE, 0 },
    // z-coordinate client configuration
    { UUID_CLIENT_CHAR_CFG, BT_ATT_READABLE | BT_ATT_WRITEABLE, 0 },
    // z-coordinate user description
    { UUID_CHAR_USER_DESC, BT_ATT_READABLE, 0 },

};

const bt_gatt_service_t bt_accel_service = {
    accel_service_attrs,
    BT_NUM_ATTRS(accel_service_attrs),
    accel_attr_read,
    accel_attr_write,
};
