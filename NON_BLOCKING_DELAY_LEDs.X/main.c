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
    unsigned long int wait = 0;
    while(1)
    {
        if(wait++ == 50000)
        {
            PORTB = ~PORTB;
            wait = 0;
        }
        
        //important code
        
    
    }
}

