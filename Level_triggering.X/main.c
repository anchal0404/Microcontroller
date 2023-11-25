
#include<xc.h>
#include "digital_keypad.h"
#pragma config WDTE = OFF
void init_config()
{
    //config of led
    PORTD = 0x00;
    TRISD = 0x00; 
    
    //config of digital keypad
    init_digital_keypad();

}


//Function to implement level triggering on switches.
void main(void)
{
    init_config();
    while(1)
    {
       /*if( (PORTB & 0x3F) == 0x3D)//When SW2 is pressed all the led glow /*Here we can write (RB0 == 0)//Switch is pressed
       {
           PORTD = 0xFD;
       }
       else if( (PORTB & 0x3F) == 0x3F)//(RB0 == 1)//Switch is released.
       {
           PORTD = 0x00;
       }*/
       if( RB0 == 0)//When SW2 is pressed all the led glow /*Here we can write (RB0 == 0)//Switch is pressed*/
       {
           PORTD = 0xFD;
       }
       else if( RB0 == 1)//(RB0 == 1)//Switch is released.
       {
           PORTD = 0x00;
       }
    }
}