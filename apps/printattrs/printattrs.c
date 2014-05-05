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

#include "bluetooth/app.h"
#include "bluetooth/host.h"

void app_setup(void)
{
    printf("print attribute table \n");

    battery_set_level(0x3f);
    accel_set_xyz(0xA1, 0xA2, 0xA3);

    bt_gatts_print();
}

void app_loop(void)
{
    bt_exit = 1;
}

void app_shutdown(void)
{
}
