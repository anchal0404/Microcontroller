
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

void main(void)
{
    init_config();
    while(1)
    {
       if( (PORTB & 0x3F) == 0x3D)//When SW2 is pressed all the leds glow
       {
           PORTD = 0xFD;
       }
       else if( (PORTB & 0x3F) == 0x3F)
       {
           PORTD = 0x00;
       }
    }
}