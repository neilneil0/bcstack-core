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

#include "btconfig.h"
#include "usrconfig.h"
#include "btutils.h"
#include "spec/att-spec.h"
#include "spec/gatt-spec.h"
#include "spec/hci-spec.h"
#include "spec/l2cap-spec.h"
#include "spec/sdp-spec.h"
#include "spec/rfcomm-spec.h"
#include "hci.h"
#include "gap.h"
#include "l2cap.h"
#include "sdp.h"
#include "gatt.h"
#include "battery-service.h"
#include "accel-service.h"
#include "blood-pressure-service.h"
#include "devinfo-service.h"

extern u8 bt_exit;

void bt_setup(void);
void bt_loop(void);
void bt_shutdown(void);

void app_setup(void);
void app_loop(void);
void app_shutdown(void);

#endif // _BLUETOOTH_H
