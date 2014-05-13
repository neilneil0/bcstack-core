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

#ifndef _BTCONFIG_H_
#define _BTCONFIG_H_

/*** L2CAP configurations ***/

// Low Energy link MTU
#define CFG_L2CAP_MTU_LE      30

// EDR link MTU
#define CFG_L2CAP_MTU_EDR     1021

/*** UART transport configurations ***/

// Host 2 Controller MTU
#define CFG_HCI_UART_MTU_H2C 128

// Controller 2 Host MTU
#define CFG_HCI_UART_MTU_C2H 128

/*** USB transport configurations ***/

#define CFG_HCI_USB_COMMAND_MTU    256
#define CFG_HCI_USB_EVENT_MTU      256
#define CFG_HCI_USB_ACL_MTU        1024

#endif // _BTCONFIG_H_
