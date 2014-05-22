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
#include <xc.h>
#include "libpic30.h"
#include "BSP.h"
#include "Timer.h"

#define H4_COMMAND_PACKET        1
#define H4_ACL_PACKET            2
#define H4_SCO_PACKET            3
#define H4_EVENT_PACKET          4

static struct {
    u8 txbuf[CFG_HCI_UART_MTU_H2C + 1];
    u8 rxbuf[CFG_HCI_UART_MTU_C2H + 1];

    u8 rxlen;
    u8 rx_event;

    struct {
        u8 up:1;
        u8 cmd_out:1;
        u8 acl_out:1;
    } flags;
} em;

void hci_setup(void)
{
    memset(&em, 0, sizeof(em));
}

void hci_shutdown(void)
{
}

void hci_write_later(u8 channel)
{
    switch (channel) {
    case BT_COMMAND_CHANNEL:
        em.flags.cmd_out = 1;
        break;
    case BT_ACL_OUT_CHANNEL:
        em.flags.acl_out = 1;
        break;
    }
}

void hci_write(u8 channel, u16 size)
{
    u8 i, dummy;

    switch (channel) {
    case BT_COMMAND_CHANNEL:
        em.txbuf[0] = H4_COMMAND_PACKET;
        break;
    case BT_ACL_OUT_CHANNEL:
        em.txbuf[0] = H4_ACL_PACKET;
        break;
    }

    IFS0bits.SPI1IF = 0;
    SPI1BUF = 0xFF;     //Set MOSI to 1
    while (!IFS0bits.SPI1IF);
    IFS0bits.SPI1IF = 0;
    dummy = SPI1BUF;
    Nop();
    Nop();
    SPI_CS_Enable();
    Nop();

    for (i = 0; i < size + 1; i++)
    {
        while (BT_MISO == 0);

        SPI1BUF = em.txbuf[i];
        while (!SPI1STATbits.SPIRBF);
        dummy = SPI1BUF;
    }
    while (BT_MISO == 0);

    SPI_CS_Release();
}

void hci_loop(void)
{
    if(em.rx_event)
    {
        em.rx_event = 0;

        switch (em.rxbuf[0]) {
        case H4_ACL_PACKET:
            hci_handle_transport_event(BT_ACL_IN_CHANNEL,
                                       em.rxbuf + 1,
                                       em.rxlen);
            break;
        case H4_EVENT_PACKET:
            hci_handle_transport_event(BT_EVENT_CHANNEL,
                                       em.rxbuf + 1,
                                       em.rxlen);
            break;
        }
    }

    if (em.flags.cmd_out) {
        em.flags.cmd_out = 0;
        hci_handle_transport_event(BT_COMMAND_CHANNEL,
                                   em.txbuf + 1,
                                   CFG_HCI_UART_MTU_H2C);
    }

    if (em.flags.acl_out) {
        em.flags.acl_out = 0;
        hci_handle_transport_event(BT_ACL_OUT_CHANNEL,
                                   em.txbuf + 1,
                                   CFG_HCI_UART_MTU_H2C);
    }
}

void em_event_input( u8* data, u8 len )
{
    if (data[0] == 1) {
        em.flags.up = 1;

        hci_write_later(BT_COMMAND_CHANNEL);
    }
}

void BT_Int_Service(void)
{
    u8 dummy;

    SPI1STATbits.SPIROV = 0;            //May9
    SPI1BUF = 0;        //pull down MOSI
    dummy = SPI1BUF;        //May9
    Nop();
    while(!SPI1STATbits.SPIRBF);
    IFS0bits.SPI1IF = 0;
    dummy = SPI1BUF;
    SPI1STATbits.SPIROV = 0;
    Nop();
    Nop();
    Nop();
    SPI_CS_Enable();

    em.rxlen = 0;

    while(BT_IRQ) {
        SPI1BUF = 0;
        SPI1STATbits.SPIROV = 0;
        while (!SPI1STATbits.SPIRBF);
        IFS0bits.SPI1IF = 0;
        em.rxbuf[em.rxlen++] = SPI1BUF;
    }
    SPI_CS_Release();

    em.rx_event = 1;
}
