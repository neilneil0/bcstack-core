#include <xc.h>

/************************************************
Function Name: void Timer1_Init(void)
Description:   Initial the Timer1,FOSC=8MHz. T1CLK = 8/2=4MHz    T1 Tips = 10ms
Inputs:        None
Returns:       None
*************************************************/
void Timer1_Init(void)
{
    T1CON = 0x0000;
    T1CONbits.TON = 1;
    T1CONbits.TCKPS = 2;            // the T1 clock prescaler is 1:64. so the T1Clock=4us
    TMR1 = 0x0000;
    PR1 = 2500;                     // 2500*16 = 40000us = 40ms
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 0;
    IPC0bits.T1IP = 3;
}

/************************************************
Function Name: void Timer2_Init(void)
Description:   Initial the Timer2
Inputs:        None
Returns:       None
*************************************************/
void Timer2_Init(void)
{

}
