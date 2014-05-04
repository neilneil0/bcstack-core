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

#ifndef _BLUETOOTH_COMMON_H
#define _BLUETOOTH_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "machine.h"
#include "bluetooth/spec/att.h"
#include "bluetooth/spec/gatt.h"
#include "bluetooth/spec/hci.h"
#include "bluetooth/gap.h"

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

#endif // _BLUETOOTH_COMMON_H
