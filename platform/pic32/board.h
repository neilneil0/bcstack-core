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


#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include "HardwareProfile.h"

// Main include for the PIC32 architecture
#include <xc.h>
#include <plib.h>

// Standard includes
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bluetooth.h"

// Macros for accessing IO ports
#define TRIS(port)     CONCAT2(TRIS, port)
#define TRISSET(port)  CONCAT3(TRIS, port, SET)
#define TRISCLR(port)  CONCAT3(TRIS, port, CLR)
#define ANSEL(port)    CONCAT2(ANSEL, port)
#define ANSELSET(port) CONCAT3(ANSEL, port, SET)
#define ANSELCLR(port) CONCAT3(ANSEL, port, CLR)
#define LAT(port)      CONCAT2(LAT, port)
#define LATSET(port)   CONCAT3(LAT, port, SET)
#define LATCLR(port)   CONCAT3(LAT, port, CLR)
#define LATINV(port)   CONCAT3(LAT, port, INV)
#define PORT(port)     CONCAT2(PORT, port)

// Helper macros
#define CONCAT2(t1, t2)        _CONCAT2_(t1, t2)
#define _CONCAT2_(t1, t2)      t1##t2
#define CONCAT3(t1, t2, t3)    _CONCAT3_(t1, t2, t3)
#define _CONCAT3_(t1, t2, t3)  t1##t2##t3


#define LED1_ON()        LATCLR(LED1_PORT) = LED1_PIN
#define LED1_OFF()       LATSET(LED1_PORT) = LED1_PIN
#define LED1_TOGGLE()    LATINV(LED1_PORT) = LED1_PIN

#define LED2_ON()        LATCLR(LED2_PORT) = LED2_PIN
#define LED2_OFF()       LATSET(LED2_PORT) = LED2_PIN
#define LED2_TOGGLE()    LATINV(LED2_PORT) = LED2_PIN

#define LED3_ON()        LATCLR(LED3_PORT) = LED3_PIN
#define LED3_OFF()       LATSET(LED3_PORT) = LED3_PIN
#define LED3_TOGGLE()    LATINV(LED3_PORT) = LED3_PIN

#define LED4_ON()        LATCLR(LED4_PORT) = LED4_PIN
#define LED4_OFF()       LATSET(LED4_PORT) = LED4_PIN
#define LED4_TOGGLE()    LATINV(LED4_PORT) = LED4_PIN

#define LED5_ON()        LATCLR(LED5_PORT) = LED5_PIN
#define LED5_OFF()       LATSET(LED5_PORT) = LED5_PIN
#define LED5_TOGGLE()    LATINV(LED5_PORT) = LED5_PIN

//Charge management
#define boardChargeMgmtInit()           {LATDCLR = _LATD_LATD7_MASK;TRISDCLR = _TRISD_TRISD7_MASK;}
#define boardChargeMgmtDataPass()       {LATDCLR = _LATD_LATD7_MASK;}
#define boardChargeMgmtBCCDP()          {LATDSET = _LATD_LATD7_MASK;}

void boardInit(void);
unsigned long board_getSystemClock(void);
unsigned long board_getPeripheralClock(void);
void initBluetoothPort(void);
void configureBtUart(uint32_t baudRate, uint8_t enableFlowControl);
u8 bt_uart_rx_byte();
void  __attribute__((nomips16)) DelayMilliSeconds(unsigned int delaymilsec);

/* Hardware specifics. */
#define TIMER_PRESCALE 8
#define configTICK_RATE_HZ          ( ( unsigned long ) 100 )

/* The priority at which the tick interrupt runs.  This should probably be
kept at 1. */
#define TICK_INTERRUPT_PRIORITY         0x01

#define TIMER3_INTERRUPT_PRIORITY       0x03

#if defined( BT_DATA_DEMO_4 ) || defined( BT_DATA_DEMO_7 )
  #define CHANGENOTIFICATION_INTERRUPT_PRIORITY CHANGE_INT_PRI_3
#else
  #define CHANGENOTIFICATION_INTERRUPT_PRIORITY CHANGE_INT_PRI_2
#endif//defined( BT_DATA_DEMO_4 )

#endif // __BOARD_H_INCLUDED__
