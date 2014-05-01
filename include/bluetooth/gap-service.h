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

#ifndef _GAP_SERVICE_H_
#define _GAP_SERVICE_H_

typedef struct {
    char* device_name;
    u16   appearance;
    u8    privacy_flag;
    struct {
        u16 min_conn_interval;
        u16 max_conn_interval;
        u16 slave_latency;
        u16 supervision_timeout_multiplier;
    } ppcp; // Peripheral Preferred Connection Parameters
} bt_gap_data_t;

extern const bt_gatt_service_t gap_service;

void gap_data_set(bt_gap_data_t* data);

#endif // _GAP_SERVICE_H_
