/*
 * NAME : Anchal Rathore
 * DATE : 1/12/2023
 * DESCRIPTION  : Implement a static clock on SSD using internal timer
 */

#include<xc.h>
#include "ssd.h"
#include "timers.h"

#pragma config WDTE = OFF /*Watchdog timer is enalble*/

unsigned int hr = 11,min = 45,flag = 0;

void init_config(void)
{
    init_ssd();
    init_timer0();
    
    /*Enable all the Global interrupts*/
    GIE = 1;
}

void main(void)
{
   static unsigned char ssd[MAX_SSD_CNT];                                                     
    static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};       
	init_config();   
	unsigned int count = 0;
	unsigned int delay = 0;
	unsigned char key ;
    /*If flag is set,for every 1/2 sec DP point will blink
     * In between every half second time will display but dp not blink
     */
    while(1)
    {
        if(flag)
        {
            ssd[0] = digit[hr/10]; //To get 2nd digit from hour
            ssd[1] = (digit[hr%10]| DP); //To get 1st digit from hour and blink dp for every 1/2 sec
            ssd[2] = digit[min/10]; //To display second digit of minute
            ssd[3] = digit[min%10]; //to display first digit of minute
        }
        else
        {
            ssd[0] = digit[hr/10];
            ssd[1] = digit[hr%10];
            ssd[2] = digit[min/10];
            ssd[3] = digit[min%10];
        }
        display(ssd);
    }
    return;
    
    
}