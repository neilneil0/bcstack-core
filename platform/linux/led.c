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

void led_state_changed(u8 new_state)
{
    u8 led0, led1, led2, led3;

    led0 = !!(new_state & 0x1);
    led1 = !!(new_state & 0x2);
    led2 = !!(new_state & 0x4);
    led3 = !!(new_state & 0x8);

    printf("--- LED STATE CHANGED <%d, %d, %d, %d> ---\n",
           led0, led1, led2, led3);
}
