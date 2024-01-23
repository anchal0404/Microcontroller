#include<xc.h>
void init_timer0(void)
{
    /*Set the internal clock source*/
    T0CS = 0;
    
    /*Assign the pre-scaler to Watchdog Timer*/
    PSA = 1;
    
    /*The timer interrupt is enabled*/
    TMR0IE = 1;
    
    /*Preset the timer ticks*/
    TMR0 = 6;
}
