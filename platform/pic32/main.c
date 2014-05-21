/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC?Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/
#include "board.h"

const uint8_t reset[] = {1, 3, 0xc, 0};
const uint8_t readver[] = {1, 3, 0x10, 0};
const uint8_t anafreq[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xFE, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x90, 0x65,
};

// host interface: h4
const uint8_t hostif[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x01, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xF9, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x03, 0x00,
};

// H4 parameters = 0x08A8
const uint8_t h4cfg[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x02, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xC0, 0x01, 0x01, 0x00, 0x00, 0x00,
    0xA8, 0x08,
    };
const uint8_t nopdisable[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x03, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xF2, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00,
};
const uint8_t baudrate[] = {
    0x01, 0x00, 0xFC, 0x15, 0xC2, 0x02, 0x00, 0x0A, 0x00, 0x04, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xEA, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x3D, 0x00, 0x00, 0x09,
};

const uint8_t warmreset[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x05, 0x00,
    0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

u8 event_ref[7] = {0x4, 0xe, 0x4, 0x1, 0x3, 0xc, 0};
u8 event[20];

u8 bt_exit = 0;

static void recv_event();

int main(void)
{
    int i;

    boardInit();
    initBluetoothPort();
    for (i=0; i<3; i++)
    {
        bt_uart_rx(event, 7);
        bt_uart_tx(reset, 4);

        DelayMilliSeconds(200);
        if (0 == memcmp(event, event_ref, 7)) break;
    }

#if 1
    bt_uart_tx(anafreq, sizeof(anafreq)); recv_event();
    bt_uart_tx(hostif, sizeof(hostif)); recv_event();
    bt_uart_tx(h4cfg, sizeof(h4cfg)); recv_event();
    bt_uart_tx(nopdisable, sizeof(nopdisable)); recv_event();
    bt_uart_tx(baudrate, sizeof(baudrate)); recv_event();
    bt_uart_tx(warmreset, sizeof(warmreset));
    DelayMilliSeconds(500);
    configureBtUart(BT_UART_WORKING_BAUD_RATE, 1);
#endif

    bt_uart_tx(readver, 4);
    recv_event();

    DelayMilliSeconds(200);

    app_setup();

    while (bt_exit == 0) {
        app_loop();
    }

    return 0;
}

static void recv_event()
{
    u8 i, len;

    memset(event, 0, 20);

    for (i=0; i<3; i++) {
        event[i] = bt_uart_rx_byte();
    }

    // data
    for (i=0; i<event[2]; i++) {
        event[i+3] = bt_uart_rx_byte();
    }
}

void led_state_changed(u8 state)
{
}
