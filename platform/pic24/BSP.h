#ifndef BSP_H
#define	BSP_H
#include <xc.h>

//#define PIC24FJ32GB004
//#define PIC24FJ64GB004
#define PIC24FJ64GA104

extern unsigned char CN_State;
extern void System_Init(void);
void Bluetooth_Start(void);
extern unsigned char SPI1_Write ( unsigned char c_trans1 );
extern unsigned char SPI1_Read(void);
extern void BT_Int_Service(void);

#ifdef PIC24FJ64GB004
#define RST_Release()       { LATAbits.LATA4 = 0; Nop();}
#define RST_Enable()        { LATAbits.LATA4 = 1; Nop();}
#define RST_TRIS    TRISAbits.TRISA4

#define SPI_CS_Enable()     { LATAbits.LATA8 = 0; Nop();}
#define SPI_CS_Release()    { LATAbits.LATA8 = 1; Nop();}
#define SPI_CS_TRIS TRISAbits.TRISA8

#define SCI_SPI_SEL()       { LATAbits.LATA9 = 1; Nop();}
#define SCI_Uart_SEL()      { LATAbits.LATA9 = 0; Nop();}
#define SPI_SEL_TRIS    TRISAbits.TRISA9

#define BT_IRQ  PORTBbits.RB14
#define BT_MISO PORTCbits.RC3

#define BT_MOSI LATBbits.LATB8
#define BT_CLK  LATCbits.LATC6

#elif defined PIC24FJ32GB004
#define RST_Release()       { LATAbits.LATA7 = 0; Nop();}
#define RST_Enable()        { LATAbits.LATA7 = 1; Nop();}
#define RST_TRIS    TRISAbits.TRISA7

#define SPI_CS_Enable()     { LATBbits.LATB4 = 0; Nop();}
#define SPI_CS_Release()    { LATBbits.LATB4 = 1; Nop();}
#define SPI_CS_TRIS TRISBbits.TRISB4

#define SCI_SPI_SEL()       { LATAbits.LATA4 = 1; Nop();}
#define SCI_Uart_SEL()      { LATAbits.LATA4 = 0; Nop();}
#define SPI_SEL_TRIS    TRISAbits.TRISA4

#define BT_IRQ  PORTCbits.RC1
#define BT_MISO PORTBbits.RB14

#define BT_MOSI LATBbits.LATB15
#define BT_CLK  LATCbits.LATC2

#else
#define RST_Release()       { LATCbits.LATC2 = 0; Nop();}
#define RST_Enable()        { LATCbits.LATC2 = 1; Nop();}
#define RST_TRIS    TRISCbits.TRISC2

#define SPI_CS_Enable()     { LATBbits.LATB15 = 0; Nop();}
#define SPI_CS_Release()    { LATBbits.LATB15 = 1; Nop();}
#define SPI_CS_TRIS TRISBbits.TRISB15

#define SCI_SPI_SEL()       { LATBbits.LATB2 = 1; Nop();}
#define SCI_Uart_SEL()      { LATBbits.LATB2 = 0; Nop();}
#define SPI_SEL_TRIS    TRISBbits.TRISB2

#define BT_IRQ  PORTBbits.RB14
#define BT_MISO PORTCbits.RC1

#define BT_MOSI LATCbits.LATC0
#define BT_CLK  LATBbits.LATB3

#endif

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* BSP_H */

