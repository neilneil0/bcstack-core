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

#ifndef _BLUETOOTH_APP_H
#define _BLUETOOTH_APP_H

#include "bluetooth/common.h"

extern u8 bt_exit;
void app_setup(void);
void app_loop(void);

#endif // _BLUETOOTH_APP_H
