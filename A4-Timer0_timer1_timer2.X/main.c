
/* 
 * File:   main.c
 * Author: Anchal Rathore
 * Descrition :Implement the time separator with Timer 0, Timer 1 and Timer 2
 * 
 * Created on 30 November 2023
 *
*/
#include<xc.h>
#include "main.h"
#include "timers.h"
 
#pragma config WDTE = OFF //Watchdog timer Enable bit(WDT disabled)

static void init_config(void)
{
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    
    init_timer0();
    init_timer1();
    init_timer2();
    
    /*Peripheral Interrupt Enable Bit(For timer2)*/
    PEIE = ON;
    
    /*Global Interrupt Enable Bit*/
    GIE = ON;
}

void main(void)
{
    init_config();
    while(1)
    {
        ;
    }
    return;
}

