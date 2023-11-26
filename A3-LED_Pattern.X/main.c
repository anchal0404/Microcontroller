/*
 * File:   main.c
 * Author: Anchal Rathore
 * Date : 24/11/2023
 * Problem Statement : Write a Embedded C program to display the multiple patterns on the LEDs controlled by the switches.
 *                     For every switch, dedicate a LEDs glow pattern.The pattern should change on key press
 */


#include <xc.h>
#include "main.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF

static void init_config(void) {
    /*To keep all LEDS OFF initially*/
    LED_ARRAY1 = OFF;
    
    /*To configure PORTD as output PORT*/
    LED_ARRAY1_DDR = 0x00; 
    
    /* Initializing digital keypad */
    init_digital_keypad();

}

void main(void) {
    //Variable declaration
    unsigned char key, key_copy;
    
    init_config();

    while (1) {
        
        /*To read key press*/
        key = read_digital_keypad(LEVEL);
        
        /*If switch is pressed, then only update key_copy*/
        if (key != ALL_RELEASED)
        {
            key_copy = key;
        }
        glow_on_press(key_copy);
    }

    return;
}

void glow_on_press(unsigned char key)
{
           
    unsigned int static flag = 0;
    static unsigned long int wait = 0;
    static unsigned long int i=0,j=0,k=0;
 
    if(wait++ == 20000)
    {
        wait  = 0;
        flag = !flag;
        if(key == SW1)
        {
            //Code for pattern1 same as assignment1
            //The LEDs should glow from Left to Right and Right to left as explained in the assignment-1.
            if(i<8)
			{
			    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 | (1 << i));
                i++;
			}
            /*Turn off LEDs from top to bottom*/
			else if(i>= 8 && i<16)
			{
			    LED_ARRAY1 = (unsigned char)(LED_ARRAY1	& ~(1<< (i - 8)));
                i++;
			}
            /*Turn on LEDs from bottom to top*/
			else if(j <= 8)
			{
			    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 | (1<<(8 - j)));
                j++;
			}
            /*Turn off LEDs from bottom to top*/
			else if(j>8 && j<=16)
			{
			    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 & ~(1<<(16 - j)));
                j++;
			}
            /*For LEDs continue running*/
            if(i == 16 && j == 17)
            {
                i=0;
                j=0;
            }
        }
    
        else if(key == SW2)
        {
            //Code for pattern2
            //The LEDs should glow from left to Right and switch off from left to right, no direction control/ direction change
            if(k<8)
            {
                LED_ARRAY1 =(unsigned char)( LED_ARRAY1 | (1<<k));
                k++;
            }
            else if(k>=8 && k<16)
            {
                LED_ARRAY1 = (unsigned char)(LED_ARRAY1 & ~(1<<(k-8)));
                k++;
            }
            if(k==16)
            {
                k=0;
            }
        }
        else if(key == SW3)
        {
            //Code for pattern3
            //The LEDs should blink alternately
            if(flag)
            {
                LED_ARRAY1 = 0xAA;
            }
            else
            {
                LED_ARRAY1 = ~LED_ARRAY1;
            }
        }
        else if( key == SW4)
        {
        //Code for pattern4
        //The LEDs has to blink nibble wise, i.e first 4 LEDs will be ON, next 4 LEDs will be OFF, 
        //after first 4 LEDs will be OFF, next 4 LEDs will be ON.
            if(flag)
            {
                LED_ARRAY1 = 0xF0;  
            }
            else
            {
                LED_ARRAY1 = ~LED_ARRAY1;
            }
        }
        else
            LED_ARRAY1 = OFF;
    }
}

