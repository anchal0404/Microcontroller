#include<xc.h>
#pragma config WDTE = OFF
void init_config()
{
    PORTB = 0x00; // make LEDs OFF
    TRISB = 0x00; // make PORTB 
}

void main(void)
{
    init_config();
    
    while(1)
    {
        PORTB = 0xFF; //Turn on all the LEDs
        for(unsigned long int wait = 100000;wait --;); //blocking delay not preferable
    
        PORTB = 0x00; //Turn on all the LEDs
        for(unsigned long int wait = 100000;wait --;);
        
        //important code
        
    
    }
}
