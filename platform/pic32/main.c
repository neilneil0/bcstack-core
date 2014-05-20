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

const uint8_t cmd[] = {1, 3, 0xc, 0};
const uint8_t anafreq[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x01, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xFE, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x90, 0x65,
};
const uint8_t nopdisable[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x02, 0x00,
    0x03, 0x70, 0x00, 0x00, 0xF2, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00,
};
const uint8_t warmreset[] = {
    0x01, 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09, 0x00, 0x03, 0x00,
    0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

u8 event_ref[7] = {0x4, 0xe, 0x4, 0x1, 0x3, 0xc, 0};
u8 event[10];

u8 bt_exit = 0;

int main(void)
{
    int i;

    boardInit();
    initBluetoothPort();
    for (i=0; i<3; i++)
    {
        bt_uart_rx(event, 7);
        bt_uart_tx(cmd, 4);

        DelayMilliSeconds(200);
        if (0 == memcmp(event, event_ref, 7)) break;
    }
 
#if 1
    bt_uart_tx(anafreq, sizeof(anafreq));
    DelayMilliSeconds(200);
    bt_uart_tx(nopdisable, sizeof(nopdisable));
    DelayMilliSeconds(200);

    bt_uart_tx(warmreset, sizeof(warmreset));
    for (i=0; i<200; i++) {
        DelayMilliSeconds(1);
        bt_uart_drain_rx_fifo();
    }

#endif
    for (i=0; i<3; i++)
    {
        bt_uart_rx(event, 7);
        bt_uart_tx(cmd, 4);

        DelayMilliSeconds(200);
        if (0 == memcmp(event, event_ref, 7)) break;
    }

    app_setup();

    while (bt_exit == 0) {
        app_loop();
    }

    return 0;
}

void led_state_changed(u8 state)
{
}
