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

#include "bluetooth/host.h"
#include "ubcsp.h"

#if 1
#define bcsp_info printf
#else
#define bcsp_info(...)
#endif

#define BCSP_INTERNAL_CHANNEL 0
#define BCSP_LE_CHANNEL 1
#define BCSP_CMDEVT_CHANNEL 5
#define BCSP_ACL_CHANNEL 6

#define BCSP_PACKET_SIZE 128

static struct bcsp_globals_t {
    struct ubcsp_packet txpkt;
    u8 txbuf[BCSP_PACKET_SIZE];

    struct ubcsp_packet rxpkt;
    u8 rxbuf[BCSP_PACKET_SIZE];

    union {
        u8     all;
        struct
        {
            u8 txready : 1,
                spare6 : 1,
                spare5 : 1,
                spare4 : 1,
                spare3 : 1,
                spare2 : 1,
                spare1 : 1,
                spare0 : 1;
        };
    } flags;
} bcsp;

void hci_setup(void)
{
    u8 activity, delay;
    int timeout;

	memset(&bcsp, 0, sizeof(bcsp));

    bt_uart_open();

	ubcsp_initialize();

	bcsp.txpkt.length = BCSP_PACKET_SIZE;
	bcsp.txpkt.payload = bcsp.txbuf;

	bcsp.rxpkt.length = BCSP_PACKET_SIZE;
	bcsp.rxpkt.payload = bcsp.rxbuf;

    bcsp.flags.all = 0;
    bcsp.flags.txready = 1;

	ubcsp_receive_packet(&bcsp.rxpkt);

    timeout = 0;
    activity = 0;
    delay = 0;
	while (1) {
		delay = ubcsp_poll(&activity);

		if (activity & UBCSP_PACKET_SENT) {
			break;
        }

		if (delay) {
			usleep(delay * 100);

			if (timeout++ > 5000) {
				bcsp_info("Initialization timed out\n");
                return;
			}
		}
	}

    bcsp_info("ubcsp initialized\n");
}

void hci_shutdown(void)
{
    bt_uart_close();
}

void hci_write_later(u8 channel)
{
    if (!bcsp.flags.txready) return;

    hci_handle_transport_event(channel, bcsp.txbuf, BCSP_PACKET_SIZE);
}

void hci_write(u8 channel, u16 size)
{
    u8 bcsp_channel = 0;

    switch (channel) {
    case BT_COMMAND_CHANNEL:
        bcsp_channel = BCSP_CMDEVT_CHANNEL;
        break;
    case BT_ACL_OUT_CHANNEL:
        bcsp_channel = BCSP_ACL_CHANNEL;
        break;
    default:
        bcsp_info("bcsp.write: unknown channel\n");
    }

	bcsp.txpkt.channel  = bcsp_channel;
	bcsp.txpkt.reliable = 1;
	bcsp.txpkt.length   = size;

    //bt_dumphex("BCSP-TX", bcsp.txpkt.payload, size);

    bcsp.flags.txready = 0;
	ubcsp_send_packet(&bcsp.txpkt);
}

void hci_loop(void)
{
    u8 delay, activity;

    delay = ubcsp_poll(&activity);

    if (activity & UBCSP_PACKET_SENT) {
        bcsp.flags.txready = 1;
        switch (bcsp.txpkt.channel) {
        case BCSP_CMDEVT_CHANNEL:
            hci_handle_transport_event(BT_COMMAND_CHANNEL, bcsp.txbuf, BCSP_PACKET_SIZE);
            break;
        case BCSP_ACL_CHANNEL:
            hci_handle_transport_event(BT_ACL_OUT_CHANNEL, bcsp.txbuf, BCSP_PACKET_SIZE);
            break;
        }
    }

    if (activity & UBCSP_PACKET_RECEIVED) {
        switch (bcsp.rxpkt.channel) {
        case BCSP_CMDEVT_CHANNEL:
            hci_handle_transport_event(BT_EVENT_CHANNEL, bcsp.rxpkt.payload, bcsp.rxpkt.length);
            break;
        case BCSP_ACL_CHANNEL:
            hci_handle_transport_event(BT_ACL_IN_CHANNEL, bcsp.rxpkt.payload, bcsp.rxpkt.length);
            break;
        default:
            bcsp_info("BCSP RX Unknown Channel 0x%x\n", bcsp.rxpkt.channel);
        }

        bcsp.rxpkt.length = BCSP_PACKET_SIZE;
        ubcsp_receive_packet(&bcsp.rxpkt);
    }

    if (delay) {
        usleep(delay * 100);
    }
}
