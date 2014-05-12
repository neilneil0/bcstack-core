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

#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

#include "spec/att.h"
#include "spec/gatt.h"
#include "spec/hci.h"
#include "spec/l2cap-spec.h"
#include "spec/sdp-spec.h"
#include "gap.h"
#include "l2cap.h"
#include "gatt.h"
#include "battery-service.h"
#include "accel-service.h"
#include "blood-pressure-service.h"
#include "devinfo-service.h"
#include "hci.h"

extern u8 bt_exit;
void bt_setup(void);
void bt_loop(void);
void bt_shutdown(void);

#if DEBUG
void bt_dumphex(char* msg, const u8* v, u16 len);
#else
#define bt_dumphex(...)
#endif

#define bt_read_u16(buffer)                     \
    ((buffer)[0] + ((buffer)[1] << 8))

#define bt_write_u16(buffer, value)             \
    do {                                        \
        (buffer)[0] = (value) & 0xFF;           \
        (buffer)[1] = (value) >> 8;             \
    } while (0)

#define bt_read_u32(buffer)                     \
    ((buffer)[0] + ((buffer)[1] << 8) +         \
     (buffer)[2] << 16 + ((buffer)[3] << 24))

#define bt_write_u32(buffer, value)             \
    do {                                        \
        (buffer)[0] = (value) & 0xFF;           \
        (buffer)[1] = ((value) >> 8) & 0xFF;    \
        (buffer)[2] = ((value) >> 16) & 0xFF;   \
        (buffer)[3] = ((value) >> 24) & 0xFF;   \
    } while (0)

#endif // _BLUETOOTH_H
