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

#ifndef _HCI_H_
#define _HCI_H_

#define BT_COMMAND_CHANNEL 1
#define BT_EVENT_CHANNEL   2
#define BT_ACL_IN_CHANNEL  3
#define BT_ACL_OUT_CHANNEL 4

void hci_setup(void);
void hci_shutdown(void);
void hci_write_later(u8 channel);
void hci_write(u8 channel, u16 size);
void hci_loop(void);

void hci_handle_transport_event(u8 channel, u8* buffer, u16 size);

void bt_uart_tx(const u8* buffer, u16 len);
void bt_uart_rx(u8* buffer, u16 len);
void bt_uart_tx_done();
void bt_uart_rx_done();

#endif //_HCI_H_
