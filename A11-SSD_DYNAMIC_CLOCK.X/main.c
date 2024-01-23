/* 
 * Name : Anchal Rathore
 * Date : 03/12/2023
 * Description: A11-Implement dynamic clock on SSD using internal timer 
 * 
 */

#include <xc.h>
#include "ssd.h"
#include "timers.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static unsigned char ssd[MAX_SSD_CNT]= {ZERO, ZERO, ZERO, ZERO};
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
int change, change1;

void init_config(void)
{
	/* to initialize ssd, digital keypad and timer0 */
	init_ssd();
	init_digital_keypad();
	init_timer0();
    init_timer2();
    
    PEIE = 1;
    GIE = 1;
}
void main(void)
{
	init_config();
    static unsigned  int min = 0, sec = 0, hour = 0, multiply = 0;
	unsigned char key , cur_key = SW3;
	int pos = -1, once = 1;
	char update = 0;
	char u_type = 0;

	while( 1 )
	{
		key = read_digital_keypad(STATE);
        
        
        if(key != ALL_RELEASED)
        { 
            cur_key = key;
        }
		/* to perform action pressing keys 
		 * to start if key 4 pressed
		 * if clock in stop mode then only if key 1, 2, 3 pressed
		 * if key 3 pressed select the position
		 * if key 1 pressed up count current position
		 * id key 2 pressed down count current position
		 */
        if(once++ == 10)
        {
            ssd[1] = ssd[1] | DP;  
            once = 0;
        }
        /*select position*/
        if( key == SW1 && (TMR0IE == 0) )
		{
            update = 1 ;
			u_type = 1;
			
		} 
         /*increase the count*/
        else if( key == SW2 && (TMR0IE == 0) )
		{           
			
            update = 1;
			u_type = 0;
            
            if(min == 0)
            {
                min = 61;
                min--;
            }
            if(hour == 0 )
            {
                hour = 25;
                hour--;
            }
		}
         /*decrease the count*/
		else if( key == SW3 && (TMR0IE == 0) )
		{
            pos = pos + 1;
            if(pos > 1)
            {
                pos = 0;
            }
			
		}
		else if ( key == SW4 )
		{
			TMR0IE = 1;
            TMR2IE = 0;
       
            /* Switching on the Timer2 */
            TMR2ON = 0;     
		}             
		/* if key 1, 2 pressed to up/down count the current position */
		if ( update )
		{
			switch ( pos )
			{
				case 0 :
					min  = (u_type) ? min + 1 : min - 1;
					break;
				
				case 1 :
					hour  = (u_type) ? hour + 1 : hour - 1;
					break;
			}

			if ( min >= 60  || min <= 0)
            {
				min = 0;
            }
			if ( hour > 23 || hour <= 0)
            {
				hour = 0;
            }
            update = 0;
        }
        if(change1 == 1)
        {
           
            if((cur_key == SW1 || cur_key == SW2 ||cur_key == SW3) && (TMR0IE == 0))
            {            
                ssd[3] = digit[min%10];
                ssd[2] = digit[min/10];
                ssd[1] = digit[hour%10];
                ssd[0] = digit[hour/10];                              
            }
            ssd[1] = ssd[1];
            
        }
        if(change1 == 2)
        {
            change1 = 0;
            if((cur_key == SW1 || cur_key == SW2 ||cur_key == SW3 )&& (TMR0IE == 0))
            {
                if(pos == 0)
                {
                    ssd[3] = 0x00;
                    ssd[2] = 0x00;
                    ssd[1] = digit[hour%10];
                    ssd[0] = digit[hour/10];                   
                }
                else if(pos == 1)
                {
                    ssd[1] = 0x00;
                    ssd[0] = 0x00;
                    ssd[3] = digit[min%10];
                    ssd[2] = digit[min/10];
                }
                
            }
	
		}
		/* if clock is in run mode */
		if ( TMR0IE )
		{                      
			// for every half sec change dot blinking;
			if ( change == 1 )
            {
				ssd[1] = ssd[1] | DP;
            }
			// for every one sec change sec value
			if( change == 7 )
			{
                change = 0;                              
				min++;
				if ( min == 60 )
				{
					min = 0;
					hour++;
				}
				if( hour >= 23)
                {
					hour = 0;
                    min = 0;   
                } 
                if(hour == 0 && min == 0)
                {
                    TMR0IE = 0;
                    TMR2IE = 1;
       
                    /* Switching on the Timer2 */                   
                    TMR2ON = 1;
                    once = 1;
                }                                 
                ssd[3] = digit[min%10];
                ssd[2] = digit[min/10];
                ssd[1] = digit[hour%10];
                ssd[0] = digit[hour/10];              
			
            }
		}
		display(ssd);
	}
}