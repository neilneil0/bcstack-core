#include <xc.h>
#include "BSP.h"

//extern unsigned char Testflag;
/*****************************************************************************************
Routine:	void __attribute__ ((__interrupt__)) _T1Interrupt(void)
Description:	timer1 interrupt
Input:		None
Output:		None
******************************************************************************************/
void __attribute__ ((interrupt,auto_psv)) _T1Interrupt()
{
    IFS0bits.T1IF = 0;
}

/*****************************************************************************************
Routine:	void __attribute__ ((__interrupt__)) _INT1Interrupt(void)
Description:	INT1 interrupt service
Input:		None
Output:		None
******************************************************************************************/
void __attribute__ ((interrupt,no_auto_psv)) _INT1Interrupt(void)
{
    IFS1bits.INT1IF = 0;
    BT_Int_Service();
}

/*****************************************************************************************
Routine:	void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt(void)
Description:	SPI1 finish interrupt
Input:		None
Output:		None
******************************************************************************************/
void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt(void)
{
    IFS0bits.SPI1IF = 0; 	//Clear Interrupt status of SPI1
}