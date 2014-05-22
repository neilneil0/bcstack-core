#include <xc.h>
#include "libpic30.h"
#include "BSP.h"
#include "Timer.h"

/**********************************************************************************************************************
 I/O define
 Bluetooth chip side                                                                    PIC24 Side
1 RST Reset pin, active high------------------------------------------------------>      RA4--RST    27
2 UART_TX/SPI_MISO UART TX/SPI data output---------------------------------------->      RC3--MISO   26
3 UART_RX/SPI_MOSI UART RX/SPI data input----------------------------------------->      RB8--MOSI   25
4 UART_RTS/SPI_SCK UART RTS/SPI clock input--------------------------------------->      RC6--SCK    24
5 UART/SPI_SEL Interface selection (1=SPI, 0=UART)-------------------------------->      RA9--SEL    23
6 UART_WU/SPI_CSN UART wakeup from sleep/deep-sleep mode/SPI chip select---------->      RA8--WAKE   15
7 UART_CTS/IRQ UART CTS/SPI interrupt request------------------------------------->      RB14-INT    14
8 VDD Main power supply----------------------------------------------------------->      3.3V
9 VDD Main power supply----------------------------------------------------------->      3.3V
10 GND Power ground--------------------------------------------------------------->      GND
 **********************************************************************************************************************/

#define SPI_MASTER  0x0120	// select 8-bit master mode, CKE=1, CKP=0
#define SPI_ENABLE  0x8000	// enable SPI port, clear status
/*****************************************************************************************
Routine:	void Oscillator_Set(void)
Description:	intial the system clock
Input:		None
Output:		None
******************************************************************************************/
void Oscillator_Set(void)
{
//    OSCCON = 0x1102;    // Enable secondary oscillator, use FRC oscillator
//    OSCCONbits.OSWEN = 1; // connect to the FRC
//    CLKDIV = 0x0001;    // FRC post-scaler (1:1), USB postscaler (1:1), CPU postscaler (1:1)
//    CLKDIVbits.RCDIV = 1;   // select the 4MHz
//    CLKDIVbits.CPDIV = 0;   // select the 32MHz
//    CLKDIVbits.DOZE = 0;
//    CLKDIVbits.PLLEN = 1;

    OSCCON = 0x1102;    // Enable secondary oscillator, use FRC oscillator
//    Current Oscillator = FRCPLL
//    New Oscillaotr = FRCPLL

    CLKDIV = 0x100;     //FRC postscaler 4MHz£¬ so Fosc=16MHz
}

/*****************************************************************************************
Routine:	void SPI1_Init(void)
Description:	intial the SPI interface.. FOSC=8MHz
Input:		None
Output:		None
******************************************************************************************/
void SPI1_Init(void)
{
    TRISAbits.TRISA7 = 1;       //enable TC1016

     __builtin_write_OSCCONL(OSCCON & 0xbf);
#ifdef PIC24FJ64GB004
    RPOR11bits.RP22R = 8;       // RP the RP22(RC6) as the SPI1_CLK. on the page 131
    TRISCbits.TRISC6 = 0;

    RPOR4bits.RP8R = 7;         // RP the RP8(RB8) as the SPI1_MOSI
    TRISBbits.TRISB8 = 0;

    RPINR20bits.SDI1R = 19;     // RP the RP19(RC3) as the SPI1_MISO
    TRISCbits.TRISC3 = 1;

    TRISBbits.TRISB14 = 1;
    RPINR0bits.INT1R = 14;      // RP the INT1 on the RB14 PIN
#elif defined PIC24FJ32GB004
    RPOR9bits.RP18R = 8;       // RP the RP18(RC2) as the SPI1_CLK.
    TRISCbits.TRISC2 = 0;

    RPOR7bits.RP15R = 7;         // RP the RP15(RB15) as the SPI1_MOSI
    TRISBbits.TRISB15 = 0;

    RPINR20bits.SDI1R = 14;     // RP the RP14(RB14) as the SPI1_MISO
    TRISBbits.TRISB14 = 1;

    TRISCbits.TRISC1 = 1;
    RPINR0bits.INT1R = 17;      // RP17 the INT1 on the RC1 PIN
#else           //PIC24FJ64GA104
    RPOR1bits.RP3R = 8;       // RP the RP3(RB3) as the SPI1_CLK.
    TRISBbits.TRISB3 = 0;

    RPOR8bits.RP16R = 7;         // RP the RP16(RC0) as the SPI1_MOSI
    TRISCbits.TRISC0 = 0;

    RPINR20bits.SDI1R = 17;     // RP the RP17(RC1) as the SPI1_MISO
    TRISCbits.TRISC1 = 1;

    TRISBbits.TRISB14 = 1;
    RPINR0bits.INT1R = 14;      // RP14 the INT1 on the RB14 PIN
#endif
    
    __builtin_write_OSCCONL(OSCCON | 0x40);

    IFS0bits.SPI1IF = 0;
    IEC0bits.SPI1IE = 0;            //No spi interrupt
    IPC2bits.SPI1IP = 4;

    //   SPI1CON1 setting
    SPI1CON1bits.DISSCK = 0;        // Internal SPI clock enable
    SPI1CON1bits.DISSDO = 0;        // SDO pin is controlled by the module
    SPI1CON1bits.MODE16 = 0;        // 8 bits wide
    SPI1CON1bits.SMP = 0;           // input data sampled at the middle of data ouput time
    SPI1CON1bits.CKE = 1;           // from active clock to idle clock - negative edge
    SPI1CON1bits.SSEN = 0;          // SSx pin not used by the module
    SPI1CON1bits.CKP = 0;           // idle state clock is low level
    SPI1CON1bits.MSTEN = 1;         // master mode
    SPI1CON1bits.SPRE = 4;          // secondary prescale 4:1    // FOSC=16MHz
    SPI1CON1bits.PPRE = 2;          // primary prescale 4:1         //SPI clock = Fosc/2/16 = 0.5MHz

    // SPI1CON2 setting
    SPI1CON2bits.FRMEN = 0;         // framed SPI support enable
    SPI1CON2bits.SPIFSD = 0;        // frame sync pulse output Master
    SPI1CON2bits.SPIFPOL = 0;       // framesync pulse is active low
    SPI1CON2bits.SPIFE = 0,         // framesync pulse precedes first bit clock
    SPI1CON2bits.SPIBEN = 0;        // enhanced buffer disable

    // SPI1STAT setting
    SPI1STATbits.SPIEN = 1;         //  inititally disable
    SPI1STATbits.SPISIDL = 0;       //  continue module operation in idle mode
    SPI1STATbits.SPIROV = 0;        //  no overflow has occured


}

/*****************************************************************************************
Routine:	void INT1_Init(void)
Description:	Intial INT1 on the RB14 by the rising edge
Input:		None
Output:		None
******************************************************************************************/
void INT1_Init(void)
{
    INTCON2bits.INT1EP = 0;     // INT1 interrupt on the rising edge
    IPC5bits.INT1IP = 3;
    IFS1bits.INT1IF = 0;
    IEC1bits.INT1IE = 1;
}

/*****************************************************************************************
Routine:	void BT_IO_init(void)
Description:	Intial the I/O
Input:		None
Output:		None
******************************************************************************************/
void BT_IO_init(void)
{
    // disable all the I/O analog function
    AD1PCFG = 0xffff;
    AD1PCFGL = 0xffff;

    //configure the Wakeup/SPICS PIN as the output
    SPI_CS_Release();
    SPI_CS_TRIS = 0;
    
    //configure the UART_SPI_SEL PIN as the output
    SPI_SEL_TRIS = 0;
    SCI_SPI_SEL();

    // configure the RST PIN as the output
    RST_TRIS = 0;
    RST_Enable();

}

/*****************************************************************************************
Routine:	void System_Init(void)
Description:	Intial the while system
Input:		None
Output:		None
******************************************************************************************/
void System_Init(void)
{
    Oscillator_Set();
    SPI1_Init();
    Timer1_Init();
}

void Bluetooth_Start(void)
{
    long i;

    // disable all the I/O analog function
    AD1PCFG = 0xffff;
    AD1PCFGL = 0xffff;

    //configure the Wakeup/SPICS PIN as the output
    SPI_CS_Release();
    SPI_CS_TRIS = 0;

    //configure the UART_SPI_SEL PIN as the output
    SPI_SEL_TRIS = 0;
    SCI_SPI_SEL();

    // configure the RST PIN as the output
    RST_TRIS = 0;
    RST_Enable();

    for(i =0x0000; i < 1000000; i ++);
    //JG. it seems the result pulse is too short
    // I have to break on the RST_Release to create a long pulse.
    INT1_Init();

    RST_Release();
}
