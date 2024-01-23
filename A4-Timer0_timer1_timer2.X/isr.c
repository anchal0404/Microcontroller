#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
    static unsigned int count0 = 0;
    static unsigned int count1 = 0;
    static unsigned int count2 = 0;
    if(TMR0IF == 1)
    {
        TMR0 = TMR0 + 6 + 2;
        if(++count0 == 20000)
        {
            count0 = 0;
            LED1 = !LED1;
        }
        TMR0IF = 0;
    }
    else if(TMR1IF == 1)
    {
        /*Re-initialise TMR1H and TMR1L to 0xFE and 0x0C to get 500 ticks*/
        TMR1H = 0xFE;              
        TMR1L = 0x0C;
        if(count1++ == 1240)
        {
            count1 = 0;
            LED2 = !LED2;
        }
        TMR1IF = 0;
    }
    else if(TMR2IF == 1)
    {
        if(++count2 == 1250)
        {
            count2 = 0;
            LED3 = !LED3;
        }
        TMR2IF = 0;
    }
}
