/*
 to toggle direction of train using digital keypad
 * File:   main.c
 * Name : Anchal Rathore
 * Date : 21.12.2023
 * Description: Implement pattern generator on LEDs controlled by switches
 * 
 */

#include <xc.h>
#include "main.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)

static void init_config(void) {
	
	/* Turn off LEDs initially */
	LED_ARRAY1 = 0x00;
	
	/* Configure as Ouput Port */
    	LED_ARRAY1_DDR  = 0X00;

	/* Initialize digital keypad */    	
	init_digital_keypad();
}

void main(void) {

    unsigned char key, flag = 1;
    unsigned int delay = 20000,i = 0,j = 0,count=0;
    
    init_config();

    while(1)
    {

		/* read digitalkeypad value store it in variable called key */
        	key = read_digital_keypad(STATE);
	
		/* remember key  holds value of key when pressed and 0x3f when released */
		
		if (key == SW1)
		{
            if(j>0 && count == 0)
            {
                count++;
                flag = 0;
            }
        	  	/* take flag as variable to toggle the direction for pattern */
			flag = !flag;
        }
		
		/* use if loops don't use blocking loops 
		   in blocking codes u cannot detect keys */
				
		if (!delay--)
		{
			
			if (flag)
			{
                if(count == 1)
                {
                    i=0;
                    count++;
                }
        			/* Code for left to right pattern */	
                if(i<8)
                {
                    delay = 20000;
                    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 | (1<<i++));
                }
                else if(i>=8 && i<16)
                {
                    delay = 20000;
                    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 & ~(1<<(i-8)));
                    i++;
                }
                else if(i>=16)
                {
                    if(count > 0)
                        i=0;
                    delay = 2000;
                    if(j<=8 && count == 0)
                    {
                        delay =20000;
                        LED_ARRAY1 =(unsigned char) (LED_ARRAY1 | (1<<(8-j)));
                        j++;
                    }
                    else if(j>8 && j<=16 && count == 0)
                    {
                        delay = 20000;
                        LED_ARRAY1 = (unsigned char)(LED_ARRAY1 & ~(1<<(16-j)));
                        j++;
                    }
                    else if(j==17)
                    {
                        i=0;
                        j=0;
                    }
                }
			}
			if (flag == 0)
			{
				/* Code for right to left pattern */
                if(j<=8)
                {
                    delay = 20000;
                    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 | (1<<(8-j)));
                    j++;
                }
                else if(j>=8 && j<=16)
                {
                    delay = 20000;
                    LED_ARRAY1 = (unsigned char)(LED_ARRAY1 & ~(1<<(16-j)));
                    j++;
                }
                else if(j==17)
                {
                    delay = 20000;
                    j=0;
                }
			}
			/* End of loop toggle flag to continue in other direction even key not pressed */
		}

     }
     return ;
}
