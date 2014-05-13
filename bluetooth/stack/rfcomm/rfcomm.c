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

u8 rfcomm_input(u8* input, u16 isize)
{
    u8 dlci;

    dlci = input[0] >> 2;
    if (dlci == 0) {
        switch (input[1]) {
        case RFCOMM_SABM:
            break;

        case RFCOMM_UA:
            break;

        case RFCOMM_DISC:
            break;

        case RFCOMM_DM:
            break;

        case RFCOMM_UIH:
            break;
        }
    }
}

u8 rfcomm_output(u8* output, u16* osize)
{
}
