#include <xc.h>
#include "digital_keypad.h"
static int count=0;

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    
    if (mode == LEVEL_DETECTION)
    {
        //count++;
        return KEYPAD_PORT & INPUT_LINES;
    }
    else
    {
        count++;
        if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            
            return KEYPAD_PORT & INPUT_LINES;
        }
        
        else if ((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED)
        {
            once = 1;
        }
        
    }
    
    return ALL_RELEASED;
}
