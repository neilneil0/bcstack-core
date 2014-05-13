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

#if DEBUG_ANY
void bt_dumphex(char* msg, const u8* v, u16 len)
{
    int i;

    printf("%s: [ ", msg);
    for (i=0; i<len; i++) printf("%02x ", v[i]);
    printf("]\n");
}
#endif
