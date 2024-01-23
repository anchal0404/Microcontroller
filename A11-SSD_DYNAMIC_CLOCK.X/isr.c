#include <xc.h>

short int change, change1 ;
void __interrupt() isr(void)
{
    static unsigned int count = 0, count3;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register value + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 8;
        
        if (count++ == 65000)
        {
            count = 0;                   
            change++ ;  
        }
 
        TMR0IF = 0;
    }
    if (TMR2IF == 1)
    {
        if (++count3 == 625)
        {
            count3 = 0;
            change1++;
            
        }                      
        TMR2IF = 0;
    }
}