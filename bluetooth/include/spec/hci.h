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

#ifndef BT_HCI_SPEC_H
#define BT_HCI_SPEC_H

#define HCI_RESET_CMD               0x0c03
#define HCI_LE_SET_ADV_PAR_CMD      0x2006
#define HCI_LE_SET_ADV_DATA_CMD     0x2008
#define HCI_LE_SET_ADV_EN_CMD       0x200A

#define HCI_DISCONN_CMPLT_EVT       0x05
#define HCI_CMD_CMPLT_EVT           0xE
#define HCI_CMD_STATUS_EVT          0xF
#define HCI_NUM_OF_CMPLT_PKTS_EVT   0x13
#define HCI_HW_ERR_EVT              0x10
#define HCI_LE_META_EVT             0x3E

#define HCI_LE_CONN_CMPLT_EVT                   0x01
#define HCI_LE_ADV_REPORT_EVT                   0x02
#define HCI_LE_CONN_UPDATE_EVT                  0x03
#define HCI_LE_READ_REMOTE_FEATURES_CMPLT_EVT   0x04
#define HCI_LE_LONG_TERM_KEY_REQ_EVT            0x05

#endif // BT_HCI_SPEC_H
