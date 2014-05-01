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

#ifndef _DEVICE_INFO_SERVICE_H_
#define _DEVICE_INFO_SERVICE_H_

typedef struct {
    const char* manufacturer_name;
    const char* model_number;
    const char* serial_number;
    const char* hardware_revision;
    const char* firmware_revision;
    const char* software_revision;
    // System ID
    // IEEE 11073-20601 Regulatory Certification Data List
    // PnP ID
} bt_device_info_t;

extern const bt_gatt_service_t device_info_service;

void device_info_set(bt_device_info_t* info);

#endif // _DEVICE_INFO_SERVICE_H_
