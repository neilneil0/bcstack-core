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

#define DEVINFO_SERVICE_UUID              0x180A
#define DEVINFO_SYSTEM_ID_UUID            0x2A23
#define DEVINFO_MODEL_NUMBER_UUID         0x2A24
#define DEVINFO_SERIAL_NUMBER_UUID        0x2A25
#define DEVINFO_FIRMWARE_REVISION_UUID    0x2A26
#define DEVINFO_HARDWARE_REVISION_UUID    0x2A27
#define DEVINFO_SOFTWARE_REVISION_UUID    0x2A28
#define DEVINFO_MANUFACTURER_NAME_UUID     0x2A29
#define DEVINFO_IEEE_DATA_UUID            0x2A2A
#define DEVINFO_PNP_ID_UUID               0x2A50

enum {
    DEVINFO_SERVICE_DECL = 0,

    DEVINFO_MANUFACTURER_NAME_DECL,
    DEVINFO_MANUFACTURER_NAME_VALUE,

    DEVINFO_MODEL_NUMBER_DECL,
    DEVINFO_MODEL_NUMBER_VALUE,

    DEVINFO_SERIAL_NUMBER_DECL,
    DEVINFO_SERIAL_NUMBER_VALUE,

    DEVINFO_HARDWARE_REVISION_DECL,
    DEVINFO_HARDWARE_REVISION_VALUE,

    DEVINFO_FIRMWARE_REVISION_DECL,
    DEVINFO_FIRMWARE_REVISION_VALUE,

    DEVINFO_SOFTWARE_REVISION_DECL,
    DEVINFO_SOFTWARE_REVISION_VALUE,

    DEVINFO_SYSTEM_ID_DECL,
    DEVINFO_SYSTEM_ID_VALUE,

    DEVINFO_IEEE_DATA_DECL,
    DEVINFO_IEEE_DATA_VALUE,

    DEVINFO_PNP_ID_DECL,
    DEVINFO_PNP_ID_VALUE,
};

static const char null_string[] = "null";
static const bt_devinfo_t null_devinfo = {
    null_string,
    null_string,
    null_string,
    null_string,
    null_string,
    null_string,
    null_string,
    null_string,
    null_string,
};

static const bt_devinfo_t* devinfo = &null_devinfo;

void devinfo_set(bt_devinfo_t* _devinfo)
{
    devinfo = _devinfo;
}

static void devinfo_attr_read(u16 handle, u8* buffer, u16* size, u16 offset)
{
    switch (handle & 0xff) {
    case DEVINFO_SERVICE_DECL:
        bt_write_u16(buffer, DEVINFO_SERVICE_UUID);
        *size = 2;
        break;

    case DEVINFO_MANUFACTURER_NAME_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_MANUFACTURER_NAME_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_MANUFACTURER_NAME_VALUE:
        *size = strlen(devinfo->manufacturer_name);
        memcpy(buffer, devinfo->manufacturer_name, *size);
        break;

    case DEVINFO_MODEL_NUMBER_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_MODEL_NUMBER_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_MODEL_NUMBER_VALUE:
        *size = strlen(devinfo->model_number);
        memcpy(buffer, devinfo->model_number, *size);
        break;

    case DEVINFO_SERIAL_NUMBER_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_SERIAL_NUMBER_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_SERIAL_NUMBER_VALUE:
        *size = strlen(devinfo->serial_number);
        memcpy(buffer, devinfo->serial_number, *size);
        break;

    case DEVINFO_HARDWARE_REVISION_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_HARDWARE_REVISION_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_HARDWARE_REVISION_VALUE:
        *size = strlen(devinfo->hardware_revision);
        memcpy(buffer, devinfo->hardware_revision, *size);
        break;

    case DEVINFO_FIRMWARE_REVISION_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_FIRMWARE_REVISION_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_FIRMWARE_REVISION_VALUE:
        *size = strlen(devinfo->firmware_revision);
        memcpy(buffer, devinfo->firmware_revision, *size);
        break;

    case DEVINFO_SOFTWARE_REVISION_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_SOFTWARE_REVISION_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_SOFTWARE_REVISION_VALUE:
        *size = strlen(devinfo->software_revision);
        memcpy(buffer, devinfo->software_revision, *size);
        break;

    case DEVINFO_SYSTEM_ID_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_SYSTEM_ID_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_SYSTEM_ID_VALUE:
        *size = strlen(devinfo->system_id);
        memcpy(buffer, devinfo->system_id, *size);
        break;

    case DEVINFO_IEEE_DATA_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_IEEE_DATA_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_IEEE_DATA_VALUE:
        *size = strlen(devinfo->ieee_data);
        memcpy(buffer, devinfo->ieee_data, *size);
        break;

    case DEVINFO_PNP_ID_DECL:
        GATT_WRITE_CHAR_DECL(buffer, handle, DEVINFO_PNP_ID_UUID,
                             BT_GATT_CHAR_READ, size);
        break;
    case DEVINFO_PNP_ID_VALUE:
        *size = strlen(devinfo->pnp_id);
        memcpy(buffer, devinfo->pnp_id, *size);
        break;

    default:
        *size = 0;
    }
}

static void devinfo_attr_write(u16 handle, u8* buffer, u16 size)
{
}

static const bt_attr_t devinfo_service_attrs[] = {
    // devinfo service declaration
    { UUID_PRIMARY_SERVICE, BT_ATT_READABLE, 18 },

    // devinfo manufacturer name declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo manufacturer name value
    { DEVINFO_MANUFACTURER_NAME_UUID, BT_ATT_READABLE, 0 },

    // devinfo model number declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo model number value
    { DEVINFO_MODEL_NUMBER_UUID, BT_ATT_READABLE, 0 },

    // devinfo serial number declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo serial number value
    { DEVINFO_SERIAL_NUMBER_UUID, BT_ATT_READABLE, 0 },

    // devinfo hardware revision declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo hardware revision value
    { DEVINFO_HARDWARE_REVISION_UUID, BT_ATT_READABLE, 0 },

    // devinfo firmware revision declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo firmware revision value
    { DEVINFO_FIRMWARE_REVISION_UUID, BT_ATT_READABLE, 0 },

    // devinfo software revision declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo software revision value
    { DEVINFO_SOFTWARE_REVISION_UUID, BT_ATT_READABLE, 0 },

    // devinfo system id declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo system id value
    { DEVINFO_SYSTEM_ID_UUID, BT_ATT_READABLE, 0 },

    // devinfo ieee data declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo ieee data value
    { DEVINFO_IEEE_DATA_UUID, BT_ATT_READABLE, 0 },

    // devinfo pnp id data declaration
    { UUID_CHAR, BT_ATT_READABLE, 1 },
    // devinfo pnp id data value
    { DEVINFO_PNP_ID_UUID, BT_ATT_READABLE, 0 },
};

const bt_gatt_service_t bt_devinfo_service = {
    devinfo_service_attrs,
    BT_NUM_ATTRS(devinfo_service_attrs),
    devinfo_attr_read,
    devinfo_attr_write,
};
