/*********************************************************************
 *
 *  Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile_xxx.h
 * Dependencies:    None
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:        Microchip C32 v1.00 or higher
 *                  Microchip C30 v3.01 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright ?2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product (?evice? which is
 *      integrated into Licensee? product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and
 *      ENC28J60.h ported to a non-Microchip device used in
 *      conjunction with a Microchip ethernet controller for the
 *      sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED ?S IS?WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

//------------------------------------------------------------------------------
// Configuration section.
// This section defines configuration settings. Change them to configure the
// system to your needs.
//------------------------------------------------------------------------------

#define BT_UART_INITIAL_BAUD_RATE   115200
#define BT_UART_WORKING_BAUD_RATE   4000000

// Log UART baud rate
#define LOG_UART_BAUD_RATE          (8 * 115200)

#define BT_CONTROLLER BT_CONTROLLER_CSR8811


#define DEV_BOARD     DEV_BOARD_BT_MX270_PIM

//------------------------------------------------------------------------------
// Supported options section.
// This sections defines possible choices for the parameters defined in the
// configuration section above.
//------------------------------------------------------------------------------

#define DEV_BOARD_EXPLORER_16    0
#define DEV_BOARD_ADB            1     // Audio Development Board
#define DEV_BOARD_BT_ADB         2     // BT Audio Development Board
#define DEV_BOARD_BT_MX270_PIM   3     // BT ADB + MX270_PIM


#define CPU_CLOCK_HZ              ( unsigned long ) 48000000UL
#define PERIPHERAL_CLOCK_HZ       ( unsigned long ) 48000000UL

// Configuration for the USART and GPIO connected to the Bluetooth controller.
//
#define BT_UART                  UART2
#define BT_UART_VECTOR           _UART_2_VECTOR
#define BT_UART_RXREG            U2RXREG
#define BT_UART_TXREG            U2TXREG

#define BT_UART_RX_PORT          C
#define BT_UART_RX_PIN           BIT_8

#define BT_UART_TX_PORT          C
#define BT_UART_TX_PIN           BIT_4

#define BT_UART_CTS_PORT         C//F
#define BT_UART_CTS_PIN          BIT_3//BIT_4

#define BT_UART_RTS_PORT         B
#define BT_UART_RTS_PIN          BIT_7

#define BT_UART_RX_REMAP_SFR     U2RXRbits.U2RXR
#define BT_UART_RX_REMAP_PIN     6 // RPC8

#define BT_UART_TX_REMAP_SFR     RPC4Rbits.RPC4R
#define BT_UART_TX_REMAP_PIN     2 // U2TX

#define BT_UART_CTS_REMAP_SFR    U2CTSRbits.U2CTSR
#define BT_UART_CTS_REMAP_PIN    7 //RPC3

#define BT_UART_RTS_REMAP_SFR    RPB7Rbits.RPB7R//RPC5Rbits.RPC5R
#define BT_UART_RTS_REMAP_PIN    2 // U2RTS

#define BT_UART_TX_DMA_CHANNEL   DMA_CHANNEL0
#define BT_UART_TX_DMA_VECTOR    _DMA_0_VECTOR
#define BT_UART_TX_DMA_INTERRUPT INT_SOURCE_DMA(BT_UART_TX_DMA_CHANNEL)
#define BT_UART_TX_IRQ           _UART2_TX_IRQ

#define BT_UART_RX_DMA_CHANNEL   DMA_CHANNEL3
#define BT_UART_RX_DMA_VECTOR    _DMA_3_VECTOR
#define BT_UART_RX_DMA_INTERRUPT INT_SOURCE_DMA(BT_UART_RX_DMA_CHANNEL)
#define BT_UART_RX_IRQ           _UART2_RX_IRQ

#define BT_RESET_PORT            C
#define BT_RESET_BIT             BIT_0

#define LOG_DMA_CHANNEL          DMA_CHANNEL1
#define LOG_DMA_VECTOR           _DMA_1_VECTOR
#define LOG_DMA_INTERRUPT        INT_SOURCE_DMA(LOG_DMA_CHANNEL)//75//

#define LOG_UART                 UART4
#define LOG_UART_VECTOR          _UART_4_VECTOR
#define LOG_UART_TX_IRQ          _UART4_TX_IRQ
#define LOG_UART_TXREG           U4TXREG

#define LOG_UART_TX_REMAP_SFR    RPF12Rbits.RPF12R
#define LOG_UART_TX_REMAP_PIN    2 // U4TX

// Configuration for storage
//
#define BT_STG_CS_PORT           B
#define BT_STG_CS_PIN            BIT_0
#define BT_STG_SPI_CHANNEL       SPI_CHANNEL2

#define BT_STG_BCLK_PORT         B
#define BT_STG_BCLK_PIN          BIT_15

#define BT_STG_SDO_PORT          A
#define BT_STG_SDO_PIN           BIT_4

#define BT_STG_SDO_REMAP_SFR     RPA4Rbits.RPA4R
#define BT_STG_SDO_REMAP_PIN     4 // SDO2

#define BT_STG_SDI_PORT          B
#define BT_STG_SDI_PIN           BIT_13

#define BT_STG_SDI_REMAP_SFR     SDI2Rbits.SDI2R
#define BT_STG_SDI_REMAP_PIN     3 // RPB13

// Configuration for volume potentiometer
#define BT_VOL_PORT              A
#define BT_VOL_PIN               BIT_0
#define BT_VOL_ADC_BUFFER        ADC1BUF0

// Configuration for LEDs:
// LED1 (D5)
#define LED1_PORT                B // Fake to I2C1_SCL
#define LED1_PIN                 BIT_8 // Fake

// LED2 (D6)
#define LED2_PORT                B // Fake to I2C1_SCL
#define LED2_PIN                 BIT_8 // Fake

// LED3 (D7)
#define LED3_PORT                B // Fake to I2C1_SCL
#define LED3_PIN                 BIT_8 // Fake

// LED4 (D8)
#define LED4_PORT                B // Fake to I2C1_SCL
#define LED4_PIN                 BIT_8 // Fake

// LED5 (D9)
#define LED5_PORT                B // Fake to I2C1_SCL
#define LED5_PIN                 BIT_8 // Fake

// Configuration for buttons:
//
#define BUTTON1_PORT              B
#define BUTTON1_PIN           BIT_2
#define EnableButton1ChangeNotice EnableCNB2

#define BUTTON2_PORT              B
#define BUTTON2_PIN           BIT_3
#define EnableButton2ChangeNotice EnableCNB3

#define BUTTON3_PORT              C
#define BUTTON3_PIN           BIT_5
#define EnableButton3ChangeNotice EnableCNC5

#define BUTTON4_PORT              C
#define BUTTON4_PIN           BIT_9
#define EnableButton4ChangeNotice EnableCNC9

#define BUTTON5_PORT              B
#define BUTTON5_PIN           BIT_5
#define EnableButton5ChangeNotice EnableCNB5

/*********************************************************************
* Macro: #define    GetSystemClock()
*
* Overview: This macro returns the system clock frequency in Hertz.
*           * value is 8 MHz x 4 PLL for PIC24
*           * value is 8 MHz/2 x 18 PLL for PIC32
*
********************************************************************/
#define GetSystemClock()    CPU_CLOCK_HZ

/*********************************************************************
* Macro: #define    GetPeripheralClock()
*
* Overview: This macro returns the peripheral clock frequency
*           used in Hertz.
*           * value for PIC24 is <PRE>(GetSystemClock()/2) </PRE>
*           * value for PIC32 is <PRE>(GetSystemClock()/(1<<OSCCONbits.PBDIV)) </PRE>
*
********************************************************************/
#define GetPeripheralClock()    (GetSystemClock() / (1 << OSCCONbits.PBDIV))

/*********************************************************************
* Macro: #define    GetInstructionClock()
*
* Overview: This macro returns instruction clock frequency
*           used in Hertz.
*           * value for PIC24 is <PRE>(GetSystemClock()/2) </PRE>
*           * value for PIC32 is <PRE>(GetSystemClock()) </PRE>
*
********************************************************************/
#define GetInstructionClock()   (GetSystemClock())


/* ################################################################## */
/*********************************************************************
* START OF GRAPHICS RELATED MACROS
********************************************************************/
/* ################################################################## */

/*********************************************************************
* AUTO GENERATED CODE
********************************************************************/

//Auto Generated Code
#define GFX_PICTAIL_V3E
#define EXPLORER_16
#define USE_8BIT_PMP
#define PIC32_GP_SK
#define GFX_USE_DISPLAY_CONTROLLER_OTM2201A
#define GFX_USE_DISPLAY_PANEL_PH480272T_005_I11Q
//End Auto Generated Code



/*********************************************************************
* END OF AUTO GENERATED CODE
********************************************************************/
#if defined (USE_16BIT_PMP)
        #error "The device selected does not support 16 bit PMP interface."
#endif

/*********************************************************************
* DISPLAY PARAMETERS
*********************************************************************/
/*
    The following are the parameters required for the
    different display drivers that is supported.
    When adding support to a new display controller or display panel,
    follow the parameterization of the driver for reusability of the
    driver.

    Display Parameter Macros Descriptions:

    1. DISP_ORIENTATION - defines the display rotation with
            respect to its native orientation. For example, if the display
            has a resolution specifications that says 240x320 (QVGA), the
            display is natively in portrait mode. If the application
            uses the display in landscape mode (320x240), then the
            orientation musts be defined as 90 or 180 degree rotation.
            The Graphics Library will calculate the actual pixel location
            to rotate the contents of the screen. So when users view the
            display, the image on the screen will come out in the correct
            orientation.

            Valid values: 0, 90, 180 and 270
            Example: #define DISP_ORIENTATION 90

    2. DISP_HOR_RESOLUTION - defines the horizontal dimension in pixels. This
            is the native horizontal dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_HOR_RESOLUTION
            of 320.

            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_HOR_RESOLUTION 320

    3. DISP_VER_RESOLUTION - defines the vertical dimension in pixels. This
            is the native vertical dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_VER_RESOLUTION
            of 240.

            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_VER_RESOLUTION 240

    4. COLOR_DEPTH - (NOTE: Define this macro in the GraphicsConfig.h
             This defines the vertical dimension in pixels.

            Valid Values: 1, 4, 8, 16, 24 (note 24 bpp is only used if you are
                          using a Display Driver that supports 24 bpp color depth.
            Example: #define COLOR_DEPTH 16

    5. DISP_DATA_WIDTH - this defines the display controller physical interface
            to the display panel.

            Valid Values: 1, 4, 8, 16, 18, 24
                          1, 4, 8 are usually used in MSTN and CSTN displays
                          16, 18 and 24 are usually used in TFT displays.
            Example: #define DISP_DATA_WIDTH 18

    6. DISP_INV_LSHIFT - this indicates that the color data is sampled in the
            falling edge of the pixel clock.

            Example: #define DISP_INV_LSHIFT - define this to sample the
                          color data in the falling edge of the pixel clock.

    7. DISP_HOR_PULSE_WIDTH - this defines the horizontal sync signal pulse width.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_PULSE_WIDTH 25

    8. DISP_VER_PULSE_WIDTH - this defines the vertical sync signal pulse width.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_PULSE_WIDTH 4

    9. DISP_HOR_BACK_PORCH - this defines the horizontal back porch.
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_BACK_PORCH 5

    10. DISP_HOR_FRONT_PORCH - this defines the horizontal front porch.
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_FRONT_PORCH 10

    11. DISP_VER_BACK_PORCH - this defines the vertical back porch.
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_BACK_PORCH 0

    12. DISP_VER_FRONT_PORCH - this defines the horizontal front porch.
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_FRONT_PORCH 2

    13. GFX_LCD_TYPE - this defines the type of display glass used.

            Valid Values: Dependent on the display controller supported LCD types.
                          GFX_LCD_TFT  // Type TFT Display
                          GFX_LCD_CSTN // Type Color STN Display
                          GFX_LCD_MSTN // Type Mono STN Display
                          GFX_LCD_OLED // Type OLED Display

            Example: #define GFX_LCD_TYPE GFX_LCD_TFT

    14. GFX_DISPLAYENABLE_ENABLE - this enables the use of the Display Enable Port
            (GEN) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports DATA ENABLE Mode. DATA ENABLE Mode
            is used when the display panel do not have sync (HSYNC and VSYNC) signals.

            Example: #define GFX_DISPLAYENABLE_ENABLE

    15. GFX_DISPLAYENABLE_POLARITY - this sets the polarity of the Display Enable Port
            (GEN) when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYENABLE_POLARITY GFX_ACTIVE_HIGH

    16. GFX_HSYNC_ENABLE - this enables the use of the Display Horizontal Synchronization
            Port (HSYNC) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports SYNC Mode. SYNC Mode
            is used when the display panel has sync (HSYNC and VSYNC) signals.

            Example: #define GFX_HSYNC_ENABLE

    17. GFX_HSYNC_POLARITY - this sets the polarity of the Display Horizontal Synchronization
            Port (HSYNC)when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_HSYNC_POLARITY GFX_ACTIVE_LOW

    18. GFX_VSYNC_ENABLE - this enables the use of the Display Vertical Synchronization
            Port (VSYNC) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports SYNC Mode. SYNC Mode
            is used when the display panel has sync (HSYNC and VSYNC) signals.

            Example: #define GFX_VSYNC_ENABLE

    19. GFX_VSYNC_POLARITY - this sets the polarity of the Display Vertical Synchronization
            Port (VSYNC)when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_VSYNC_POLARITY GFX_ACTIVE_LOW

    20. GFX_DISPLAYPOWER_ENABLE - this enables the use of the Display Power Sequencer
            Control Port (GPWR) when using the Microchip Graphics Module. The signal
            can be used to control the display power circuitry. The Graphics Module
            can manage the powering up and powering down of the display since
            power up and power down sequence in display panels is essential to
            extend display life cycle.

            Example: #define GFX_DISPLAYPOWER_ENABLE

    21. GFX_DISPLAYPOWER_POLARITY - this sets the polarity of the Display Power Sequencer
            Control Port (GPWR) when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYPOWER_POLARITY GFX_ACTIVE_HIGH

    22. GFX_CLOCK_POLARITY - this sets the polarity of the Display Glass Clock Port (GCLK)
            when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_CLOCK_POLARITY GFX_ACTIVE_HIGH


    There are two major types of controllers enumerated here:
    1. Controllers in Smart Displays - these are display modules that have
       built in display controller. Interface to the PIC device(s)
       are usually through parallel interface or serial interface.

       Required parameters:
       #define DISP_ORIENTATION
       #define DISP_HOR_RESOLUTION
       #define DISP_VER_RESOLUTION

    2. Controller that drives the RGB Glass directly - these are display
       controllers that comes in a separate package or built into the
       microcontrollers.

       Required parameters:
       #define DISP_ORIENTATION
       #define DISP_HOR_RESOLUTION
       #define DISP_VER_RESOLUTION
       #define DISP_DATA_WIDTH
       #define DISP_HOR_PULSE_WIDTH
       #define DISP_HOR_BACK_PORCH
       #define DISP_HOR_FRONT_PORCH
       #define DISP_VER_PULSE_WIDTH
       #define DISP_VER_BACK_PORCH
       #define DISP_VER_FRONT_PORCH

       Optional parameters:
       #define DISP_INV_LSHIFT

       When using Microchip Graphics Module (mchpGfxDrv) required parameters:
       #define GFX_DISPLAYENABLE_ENABLE
       #define GFX_DISPLAYENABLE_POLARITY

       or

       #define GFX_HSYNC_ENABLE
       #define GFX_VSYNC_ENABLE
       #define GFX_HSYNC_POLARITY
       #define GFX_VSYNC_POLARITY

       #define GFX_CLOCK_POLARITY

       When using Microchip Graphics Module (mchpGfxDrv) Optional parameters:
       #define GFX_DISPLAYPOWER_ENABLE
       #define GFX_DISPLAYPOWER_POLARITY


*/

// -----------------------------------
// For SMART DISPLAYS
// -----------------------------------
#if defined (GFX_USE_DISPLAY_PANEL_PH480272T_005_I11Q)
    #define DISP_ORIENTATION        90
    #define DISP_HOR_RESOLUTION     176
    #define DISP_VER_RESOLUTION     220
#endif

/*********************************************************************
* DISPLAY PARALLEL INTERFACE
*********************************************************************/
/*
   Select the correct Parallel Master Port Interface Driver.
   This selection is valid only for parallel interface. When using
   display drivers that uses serial interface, this portion should be
   commented out or removed.
*/
#define USE_GFX_PMP

/*********************************************************************
* PARALLEL MASTER PORT INTERFACE TIMING
*********************************************************************/
    // When using the Parallel Master Port (or Enhanced Parallel Master Port) the
    // PMP timing must be defined for the following:
    // PMP_DATA_SETUP_TIME or EPMPCSx_DATA_SETUP (for DWAITB)
    // PMP_DATA_WAIT_TIME or EPMPCSx_DATA_WAIT_TIME (for DWAITM)
    // and PMP_DATA_HOLD_TIME or EPMPCSx_DATA_HOLD_TIME (for DWAITE)
    // where x is 1 or 2 (EPMP has 2 chip selects)
    // All values are timing parameters in ns.
    // The timing is dependent on the display controller sampling period if
    // interfacing with the display controller or device AC timing requirements
    // if interfacing with a device (such as SRAM or Parallel Flash memory).
    // Refer to your specific display controller or device to determine the
    // optimum (fastest) timing requirement for your interface.
#if defined (GFX_USE_DISPLAY_CONTROLLER_OTM2201A)
#define PMP_DATA_SETUP_TIME                (1)
#define PMP_DATA_WAIT_TIME                 (40)  // See HX8347 data sheet for details
#define PMP_DATA_HOLD_TIME                 (1)
#endif

/*********************************************************************
* HARDWARE PROFILE FOR DISPLAY CONTROLLER INTERFACE
*********************************************************************/
/*
    The following defines the different IO signals used to connect
    to the display controller.
    The hardware profile used is dependent on the PIC device
    and the development board used.

    The following are used to control the following signals to the
    Display Controller:
    1. Reset Signal - this signal controls the reset pin of the display
            controller if available.

            Example:
            #define DisplayResetConfig()        TRISAbits.TRISA4 = 0
            #define DisplayResetEnable()        LATAbits.LATA4 = 0
            #define DisplayResetDisable()       LATAbits.LATA4 = 1

    2. Command/Data Signal - this signal indicates to the controller
            if the command or data is being sent to the display controller.

            Example:
            #define DisplayCmdDataConfig()      TRISAbits.TRISA1 = 0
            #define DisplaySetCommand()         LATAbits.LATA1 = 0
            #define DisplaySetData()            LATAbits.LATA1 = 1

    3. Controller Chip Select Signal - this signal controls the chip select
            pin of the display controller is available.

            Example:
            #define DisplayConfig()             TRISBbits.TRISB15 = 0
            #define DisplayEnable()             LATBbits.LATB15 = 0
            #define DisplayDisable()            LATBbits.LATB15 = 1

    4. Display Module Power Control Signal - this signal turns on or off
            the display module if available. In some cases, this can be an
            IO port that will enable the power circuitry of your
            display module.

            Example:
            #define DisplayPowerConfig()        TRISAbits.TRISA5 = 0
            #define DisplayPowerOn()            LATAbits.LATA5 = 1
            #define DisplayPowerOff()           LATAbits.LATA5 = 0

    5. Display Backlight Brightness Control - this controls the backlight
            brightness or ON or OFF states if available. If brightness is
            controllable, this signal may be driven by some PWM signal.

            Example:
            #define DisplayBacklightConfig()    TRISDbits.TRISD0 = 0
            #define DisplayBacklightOn()        LATDbits.LATD0 = 0
            #define DisplayBacklightOff()       LATDbits.LATD0 = 1

*/

/*********************************************************************
 * IOS FOR THE DISPLAY CONTROLLER
 *********************************************************************/
#define DisplayConfig()             TRISDCLR = _TRISD_TRISD11_MASK
#define DisplayEnable()             LATDCLR = _LATD_LATD11_MASK     //ADK Checked
#define DisplayDisable()            LATDSET = _LATD_LATD11_MASK     //ADK Checked

#define DisplayCmdDataConfig()      TRISBCLR = _TRISB_TRISB15_MASK
#define DisplaySetCommand()         LATBCLR = _LATB_LATB15_MASK
#define DisplaySetData()            LATBSET = _LATB_LATB15_MASK

#define DisplayResetConfig()        TRISCCLR = _TRISC_TRISC1_MASK    //ADK Checked
#define DisplayResetEnable()        LATCCLR =  _LATC_LATC1_MASK       //ADK Checked
#define DisplayResetDisable()       LATCSET =  _LATC_LATC1_MASK       //ADK Checked

#define DisplayBacklightOff()
#define DisplayBacklightConfig()

#endif // __HARDWARE_PROFILE_H


