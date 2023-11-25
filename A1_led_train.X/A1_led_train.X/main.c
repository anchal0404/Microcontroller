/*
 * File:   main.c
 * Author: Anchal Rathore
 * Date: 16-11-2023
 * Description: This program will toggle the LEDs at PORTD
 * It illustrates coding practices and conventions used in this course.
 */

#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

/* Function: init_config()
 * Description: This function is used to setup initial peripheral
 * configuration, like setting port directions, initializing port values
 */
static void init_config(void) {
    LED_ARRAY1_DDR = 0x00; // Set direction to o/p
     LED_ARRAY1 = 0x00;     // Set initial port value
}

void main(void) 
{
    init_config();

    unsigned int long wait = 10000;
    int i,j;
   

    while (1) 
	{
        //Non blocking delay
		if(wait++ == 10000)
		{
			wait = 0;
            /*Turn on LEDs from top of bottom*/
			if(i<8)
			{
			    LED_ARRAY1 = LED_ARRAY1 | (1 << i);
                i++;
			}
            /*Turn off LEDs from top to bottom*/
			else if(i>= 8 && i<16)
			{
			    LED_ARRAY1 = LED_ARRAY1	& ~(1<< (i - 8));
                i++;
			}
            /*Turn on LEDs from bottom to top*/
			else if(j <= 8)
			{
			    LED_ARRAY1 = LED_ARRAY1 | (1<<(8 - j));
                j++;
			}
            /*Turn off LEDs from bottom to top*/
			else if(j>8 && j<=17)
			{
			    LED_ARRAY1 = LED_ARRAY1 & ~(1<<(16 - j));
                j++;
			}
            /*For LEDs continue running*/
            if(i == 16 && j == 17)
            {
                i=0;
                j=0;
            }
			
		}
    }   
}
