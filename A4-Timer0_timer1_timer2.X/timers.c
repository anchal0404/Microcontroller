#include<xc.h>
#include "timers.h"

void init_timer0(void)
{
    /*TMR0 Clock Source Select bit for Internal clk cycle*/
    T0CS = 0;
    
    /* Prescaler is assigned to the WDT*/
    PSA = 1;
    
    TMR0 = 6;
    
    /*Timer interrupt is Enable*/
    TMR0IE = 1;
}

void init_timer1(void)
{
    /*Timer1 Input Clock Prescale Select bits 1:8*/
    
    T1CKPS1 = 1;
    T1CKPS0 = 1;
    
    
    TMR1H = 0xFE;
    TMR1L = 0x0C;
    
    /*Selecting internal clk src*/
    TMR1CS = 0;
    
    /*Enable Timer 1 Interrupt */
    TMR1IE = 1;
    
    /*Set Timer1 On bit*/
    TMR1ON = 1;
}
void init_timer2(void)
{
    /*Timer1 Input Clock Pre-scale Select bits 1:8*/
    T2CKPS0 = 1;
    T2CKPS1 = 1;
    
    /*Enable Interrupt in timer 2*/
    TMR2IE = 1;
    
    /* Loading the Pre Load register with 250 */
    PR2 = 250;
    
    /*Turn on timer 2*/
    TMR2ON = 1; 
    
}