/*
 * File:   main.c
 * NAME : ANCHAL RATHORE
 * DATE : 20.11.2023
 * DESCRIPTION: Implement a left scrolling number marquee
 */

#include <xc.h>
#include "ssd.h"
#pragma config WDTE = OFF   // Watchdog Timer Enable bit (WDT disabled)
//static unsigned char ssd[MAX_SSD_CNT]={ZERO, ZERO, ZERO, ZERO};
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDERSCORE, UNDERSCORE};

     

static void init_config(void) {
    init_ssd();
}
 
void main(void) {
    unsigned char ssd[MAX_SSD_CNT]; //optional
    unsigned int i = 0 ,delay = 0;
    init_config();

    while (1) {
        if(delay++ == 150)
        {
            delay = 0;
            if(i++ >= 11)
            {
                i=0;
            }
        }
	/* shift the numbers 0123 to 1234 to 3456  .... to 6789 to 789_ 89_ _ to 9__0 to __01*/
        /* 0++ ,1++,2++,3++ -> 1234 */
        ssd[0] = digit[i];
        ssd[1] = digit[(i+1)%12];
        ssd[2] = digit[(i+2)%12];
        ssd[3] = digit[(i+3)%12];
        
        display(ssd);
    }
    return;
}
