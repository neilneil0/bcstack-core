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

#ifndef _SDP_H_
#define _SDP_H_

typedef struct _sdp_attr_t {
    u16 attr_id;
    const u8* attr_value;
    u8 length;
} sdp_attr_t;

typedef struct _sdp_record_t {
    const sdp_attr_t* attrs;
    u8 count;
} sdp_record_t;

#endif // _SDP_H_
