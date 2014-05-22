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

#if DEBUG_H4
#define h4_printf printf
#else
#define h4_printf(...)
#endif

#define H4_COMMAND_PACKET        1
#define H4_ACL_PACKET            2
#define H4_SCO_PACKET            3
#define H4_EVENT_PACKET          4

enum {
    H4_RX_PACKET_ID = 1,
    H4_RX_ACL_HEADER,
    H4_RX_ACL_PAYLOAD,
    H4_RX_EVENT_HEADER,
    H4_RX_EVENT_PAYLOAD,
};

static struct {
    u8 tx_dma_ready;
    u8 tx_dma_event;
    u8 rx_dma_event;
    u8 rx_state;
    u8 txbuf[CFG_HCI_UART_MTU_H2C + 1];
    u8 rxbuf[CFG_HCI_UART_MTU_C2H + 1];
} h4;

void hci_setup(void)
{
    memset(&h4, 0, sizeof(h4));

    h4.tx_dma_ready = 1;

    h4.rx_state = H4_RX_PACKET_ID;
    bt_uart_rx(h4.rxbuf, 1);
}

void hci_shutdown(void)
{
}

void hci_write_later(u8 channel)
{
    if (!h4.tx_dma_ready) return;

    hci_handle_transport_event(channel, h4.txbuf + 1, CFG_HCI_UART_MTU_H2C);
}

void hci_write(u8 channel, u16 size)
{
    h4.tx_dma_ready = 0;

    switch (channel) {
    case BT_COMMAND_CHANNEL:
        h4.txbuf[0] = H4_COMMAND_PACKET;
        break;
    case BT_ACL_OUT_CHANNEL:
        h4.txbuf[0] = H4_ACL_PACKET;
        break;
    }

    bt_uart_tx(h4.txbuf, size + 1);
}

void hci_loop(void)
{
    u16 payload_len;
    u8 channel;

    if (h4.tx_dma_event) {
        h4.tx_dma_event = 0;
        h4.tx_dma_ready = 1;

        switch (h4.txbuf[0]) {
        case H4_COMMAND_PACKET:
            channel = BT_COMMAND_CHANNEL;
            break;
        case H4_ACL_PACKET:
            channel = BT_ACL_OUT_CHANNEL;
            break;
        }

        hci_handle_transport_event(channel, h4.txbuf + 1, CFG_HCI_UART_MTU_H2C);
    }

    if (h4.rx_dma_event) {
        h4.rx_dma_event = 0;

        switch (h4.rx_state) {
        case H4_RX_PACKET_ID:
            switch (h4.rxbuf[0]) {
            case H4_ACL_PACKET:
                h4.rx_state = H4_RX_ACL_HEADER;
                bt_uart_rx(h4.rxbuf + 1, 4);
                break;
            case H4_EVENT_PACKET:
                h4.rx_state = H4_RX_EVENT_HEADER;
                bt_uart_rx(h4.rxbuf + 1, 2);
                break;
            }
            break;
        case H4_RX_ACL_HEADER:
            h4.rx_state = H4_RX_ACL_PAYLOAD;
            payload_len = bt_read_u16(h4.rxbuf + 3);
            bt_uart_rx(h4.rxbuf + 5, payload_len);
            break;
        case H4_RX_ACL_PAYLOAD:
            payload_len = bt_read_u16(h4.rxbuf + 3);
            hci_handle_transport_event(BT_ACL_IN_CHANNEL, h4.rxbuf + 1, payload_len + 4);
            h4.rx_state = H4_RX_PACKET_ID;
            bt_uart_rx(h4.rxbuf, 1);
            break;
        case H4_RX_EVENT_HEADER:
            h4.rx_state = H4_RX_EVENT_PAYLOAD;
            payload_len = h4.rxbuf[2];
            bt_uart_rx(h4.rxbuf + 3, payload_len);
            break;
        case H4_RX_EVENT_PAYLOAD:
            payload_len = h4.rxbuf[2];
            hci_handle_transport_event(BT_EVENT_CHANNEL, h4.rxbuf + 1, payload_len + 2);
            h4.rx_state = H4_RX_PACKET_ID;
            bt_uart_rx(h4.rxbuf, 1);
            break;
        }
    }
}

void bt_uart_tx_dma_done()
{
    h4.tx_dma_event = 1;
}

void bt_uart_rx_dma_done()
{
    h4.rx_dma_event = 1;
}
