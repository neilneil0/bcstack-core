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

// System Clocking
// SYSCLK = 48 MHz ((12MHz Crystal/FPLLIDIV) * FPLLMUL / FPLLODIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
#pragma config FPLLIDIV = DIV_3 // PLL Input Divider
#pragma config FPLLMUL = MUL_24 // PLL Multiplier
#pragma config FPLLODIV = DIV_2 // System PLL Output Clock Divider
#pragma config FNOSC = PRIPLL   // Oscillator Selection Bits: Primary Oscillator with PLL
#pragma config POSCMOD = HS     // Primary Oscillator: HS Oscillator Mode

//#pragma config FCKSM = CSDCMD // Clock Switch DISABLED, Fail-Save Clock Monitor DISABLED
//#pragma config FSOSCEN = OFF  // Secondary Oscillator Enable
//#pragma config IESO = OFF     // Internal/External Switch Over (Two-Speed Startup)
//#pragma config OSCIOFNC = OFF // CLKO Output Signal Active on OSCO Pin

// Peripheral Bus Clocking
// PBCLK = 48 MHz
#pragma config FPBDIV = DIV_1   // Peripheral Clock Divisor: PB clock = Sys_CLK/2

// Peripheral Pins Select
//#pragma config PMDL1WAY = OFF // Peripheral Module Disable Configuration: Allow multiple reconfigurations
//#pragma config IOL1WAY = OFF  // Peripheral Pin Select Configuration: Allow multiple reconfigurations

// Watchdog Timer
//#pragma config WDTPS = PS128  // Watchdog Timer Postscaler: 1:128
#pragma config FWDTEN = OFF     // Watchdog Timer Enable

// Debugging
#pragma config DEBUG = ON       // Background Debugger Enable (Debugger is enabled)
#pragma config ICESEL=ICS_PGx4  // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)

// Memory Protection
#pragma config PWP = OFF        // Program Flash Write Protect (Disable)
#pragma config BWP = OFF        // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF         // Code Protect (Protection Disabled)

// USB
#pragma config UPLLIDIV = DIV_3 // USB PLL Input Divider
#pragma config UPLLEN = ON      // USB PLL Enable

#pragma config FUSBIDIO = OFF   // USB USID Selection (Controlled by Port Function)
#pragma config FVBUSONIO = OFF  // USB VBUS ON Selection (Controlled by Port Function)

static volatile uint32_t intStatus;

static void configureDma();

void boardInit(void)
{

    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig(board_getSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Setup to use the external interrupt controller.
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // Enable interrupts
    INTEnableInterrupts();

    // JTAG port has to be disabled in order for LEDs to work.
    // When ICD3 is used as a debugger it disables JTAG automatically.
    // It does not do so if it is used as a programmer.
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    // Make Ports A&B&F&G digital
    ANSELACLR = 0xFFFF;
    ANSELBCLR = 0xFFFF;
    #if (DEV_BOARD == DEV_BOARD_BT_MX270_PIM)
    ANSELCCLR = 0xFFFF;
    #else
    ANSELFCLR = 0xFFFF;
    ANSELGCLR = 0xFFFF;
    #endif

    // Enable Change Notice peripheral on port A.
    // Do not enable any specific change notices. They are enabled in the modules that use them.
    mCNCOpen(CNC_ON | CNC_IDLE_CON, 0, 0);
    mCNCClearIntFlag();
    mCNCIntEnable(1);

    // Enable Change Notice peripheral on port B.
    // Do not enable any specific change notices. They are enabled in the modules that use them.
    mCNBOpen(CNB_ON | CNB_IDLE_CON, 0, 0);
    mCNBClearIntFlag();
    mCNBIntEnable(1);

    // Set priority of the notification interrupt.
    mCNSetIntPriority(CHANGENOTIFICATION_INTERRUPT_PRIORITY);

}


unsigned long board_getSystemClock(void)
{
    return CPU_CLOCK_HZ;
}


unsigned long board_getPeripheralClock(void)
{
    return PERIPHERAL_CLOCK_HZ;
}


void __attribute__((nomips16)) board_delayUS(UINT16 us)
{
    UINT32 start = _CP0_GET_COUNT();
    UINT32 end = start + CPU_CLOCK_HZ / 1000000 / 2 * us;
    if (end > start)
        while (_CP0_GET_COUNT() < end);
    else
        while (_CP0_GET_COUNT() > start || _CP0_GET_COUNT() < end);
}


void initBluetoothPort(void)
{
    unsigned long tmp, tmp2;
    unsigned long clock;

    // Configure BT RESET pin and assert it
    LATCLR(BT_RESET_PORT) = BT_RESET_BIT;   // Reset the BT module
    TRISCLR(BT_RESET_PORT) = BT_RESET_BIT;  // Configure  BT RESET pin for output

    // Configure BT RTS pin as output and set it
    LATSET(BT_UART_RTS_PORT) = BT_UART_RTS_PIN;
    TRISCLR(BT_UART_RTS_PORT) = BT_UART_RTS_PIN;

    // Configure BT TX pin as output and set it
    LATSET(BT_UART_TX_PORT) = BT_UART_TX_PIN;
    TRISCLR(BT_UART_TX_PORT) = BT_UART_TX_PIN;

    // Configure BT RX pin
    TRISSET(BT_UART_RX_PORT) = BT_UART_RX_PIN;     // Configure  BT RX pin for input
    ANSELCLR(BT_UART_RX_PORT) = BT_UART_RX_PIN;    // Disable analog function on BT RX pin

    // Configure BT CTS pin
    TRISSET(BT_UART_CTS_PORT) = BT_UART_CTS_PIN;   // Configure  BT CTS pin for input
    ANSELCLR(BT_UART_CTS_PORT) = BT_UART_CTS_PIN;  // Disable analog function on BT CTS pin

    // Connect BT RX pin to BT UART
    BT_UART_RX_REMAP_SFR = BT_UART_RX_REMAP_PIN;

    // Connect BT CTS pin to BT CTS
    BT_UART_CTS_REMAP_SFR = BT_UART_CTS_REMAP_PIN;

    // Connect BT TX pin to BT UART
    BT_UART_TX_REMAP_SFR = BT_UART_TX_REMAP_PIN;

    // Connect BT RTS pin to BT UART
    BT_UART_RTS_REMAP_SFR = BT_UART_RTS_REMAP_PIN;

    // Calculate actual working baud rate
    if (BT_UART_WORKING_BAUD_RATE > (115200 * 2))
    {
        clock = board_getPeripheralClock() / 4;
        tmp2 = clock % BT_UART_WORKING_BAUD_RATE;
        tmp = clock / BT_UART_WORKING_BAUD_RATE - (tmp2 >= BT_UART_WORKING_BAUD_RATE / 2 ? 0 : 1);
        tmp = clock / (tmp + 1);
    }
    else
    {
        clock = board_getPeripheralClock() / 16;
        tmp2 = clock % BT_UART_WORKING_BAUD_RATE;
        tmp = clock / BT_UART_WORKING_BAUD_RATE - (tmp2 >= BT_UART_WORKING_BAUD_RATE / 2 ? 0 : 1);
        tmp = clock / (tmp + 1);
    }

//    // Configure BT UART interrupt
    INTSetVectorPriority(INT_VECTOR_UART(BT_UART), 5);
    INTSetVectorSubPriority(INT_VECTOR_UART(BT_UART), INT_SUB_PRIORITY_LEVEL_0);

    LATSET(BT_RESET_PORT) = BT_RESET_BIT;   // Deactivate BT module reset

    // Configure UART for the initial baud rate with CTS/RTS flow controll
    configureBtUart(BT_UART_INITIAL_BAUD_RATE, 1);

}

void configureBtUart(uint32_t baudRate, uint8_t enableFlowControl)
{
    if (baudRate != 0)
    {
        // Configure BT UART
        if (baudRate > (115200 * 2))
            UARTConfigure(BT_UART, (enableFlowControl ? UART_ENABLE_PINS_CTS_RTS | UART_RTS_WHEN_RX_NOT_FULL : 0) | UART_ENABLE_HIGH_SPEED);
        else
            UARTConfigure(BT_UART, (enableFlowControl ? UART_ENABLE_PINS_CTS_RTS | UART_RTS_WHEN_RX_NOT_FULL : 0));

        UARTSetFifoMode(BT_UART, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
        UARTSetLineControl(BT_UART, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
        baudRate = UARTSetDataRate(BT_UART, board_getPeripheralClock(), baudRate);

        configureDma();
        
        // Enable UART
        UARTEnable(BT_UART, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    }
    else
    {
        // Configure BT TX pin as GPIO so that it remains high after
        // disabling the UART.
        TRISCLR(BT_UART_TX_PORT) = BT_UART_TX_PIN;
        LATSET(BT_UART_TX_PORT) = BT_UART_TX_PIN;

        // Disable UART
        UARTEnable(BT_UART, UART_DISABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    }
}

static void configureDma()
{
    /* Enable the DMA module */
    DmaWriteGlobalFlags(DMA_GFLG_ON);

    /* Configure RX DMA */
    DmaChnConfigure(BT_UART_RX_DMA_CHANNEL, DMA_CHN_PRI0, DMA_CONFIG_DEFAULT);
    DmaChnSetEventControl(BT_UART_RX_DMA_CHANNEL,
                        DMA_EV_START_IRQ_EN|
                        DMA_EV_START_IRQ(BT_UART_RX_IRQ));

    DmaChnSetEvEnableFlags(BT_UART_RX_DMA_CHANNEL,DMA_EV_BLOCK_DONE);
    INTSetVectorPriority(INT_VECTOR_DMA(BT_UART_RX_DMA_CHANNEL), 5);
    INTSetVectorSubPriority(INT_VECTOR_DMA(BT_UART_RX_DMA_CHANNEL), INT_SUB_PRIORITY_LEVEL_0);
    INTClearFlag(BT_UART_RX_DMA_INTERRUPT);
    DmaChnClrEvFlags(BT_UART_RX_DMA_CHANNEL, DMA_EV_BLOCK_DONE);
    INTEnable(BT_UART_RX_DMA_INTERRUPT, INT_ENABLED);

    /* Configure TX DMA */
    DmaChnConfigure(BT_UART_TX_DMA_CHANNEL, DMA_CHN_PRI0, DMA_CONFIG_DEFAULT);
    DmaChnSetEventControl(BT_UART_TX_DMA_CHANNEL,
                        DMA_EV_START_IRQ_EN|
                        DMA_EV_START_IRQ(BT_UART_TX_IRQ));

    DmaChnSetEvEnableFlags(BT_UART_TX_DMA_CHANNEL, DMA_EV_BLOCK_DONE);
    INTSetVectorPriority(INT_VECTOR_DMA(BT_UART_TX_DMA_CHANNEL), 5);
    INTSetVectorSubPriority(INT_VECTOR_DMA(BT_UART_TX_DMA_CHANNEL), INT_SUB_PRIORITY_LEVEL_0);
    INTClearFlag(BT_UART_TX_DMA_INTERRUPT);
    DmaChnClrEvFlags(BT_UART_TX_DMA_CHANNEL, DMA_EV_BLOCK_DONE);
    INTEnable(BT_UART_TX_DMA_INTERRUPT, INT_ENABLED);
}

void bt_uart_tx(const u8* buffer, u16 len)
{
    intStatus = INTDisableInterrupts();
    {
        DmaChnSetTxfer(BT_UART_TX_DMA_CHANNEL, buffer, (void*)&BT_UART_TXREG, len, 1, 1);
        DmaChnEnable(BT_UART_TX_DMA_CHANNEL);
    }
    INTRestoreInterrupts(intStatus);
}

void bt_uart_rx(u8* buffer, u16 len)
{
    intStatus = INTDisableInterrupts();
    {
        DmaChnSetTxfer(BT_UART_RX_DMA_CHANNEL, (void*)&BT_UART_RXREG, buffer, 1, len, 1);
        DmaChnEnable(BT_UART_RX_DMA_CHANNEL);

    }
    INTRestoreInterrupts(intStatus);
}

u8 bt_uart_rx_byte()
{
    while (!UARTReceivedDataIsAvailable(BT_UART));
    return UARTGetDataByte(BT_UART);
}

void  __attribute__((nomips16)) DelayMilliSeconds(unsigned int delaymilsec)
{
    unsigned int count_value=0;
    unsigned int delay_time=0;
    unsigned int match_value=0;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(count_value));
    delay_time = ((CPU_CLOCK_HZ/2/1000)*delaymilsec);
    match_value = delay_time + count_value;

    /* Wait for the given number of milliseconds */
    while(count_value < match_value)
    {
            // get the latest count value
            asm volatile("mfc0   %0, $9" : "=r"(count_value));
    }
}

void __attribute__( (interrupt(ipl5), vector(BT_UART_RX_DMA_VECTOR)))  __attribute__((nomips16)) btUartRxDmaInterruptHandler(void);

void  __attribute__((nomips16)) btUartRxDmaInterruptHandler(void)
{
    INTClearFlag(BT_UART_RX_DMA_INTERRUPT);
    DmaChnClrEvFlags(BT_UART_RX_DMA_CHANNEL, DMA_EV_BLOCK_DONE);

    bt_uart_rx_dma_done();
}

void __attribute__( (interrupt(ipl5), vector(BT_UART_TX_DMA_VECTOR)))  __attribute__((nomips16)) btUartTxDmaInterruptHandler(void);

void  __attribute__((nomips16)) btUartTxDmaInterruptHandler(void)
{
    INTClearFlag(BT_UART_TX_DMA_INTERRUPT);
    DmaChnClrEvFlags(BT_UART_TX_DMA_CHANNEL, DMA_EV_BLOCK_DONE);

    bt_uart_tx_dma_done();
}
