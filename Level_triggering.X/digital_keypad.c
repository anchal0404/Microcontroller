#include<xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    TRISB = TRISB | 0x3F; 
}
