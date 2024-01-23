
#include<xc.h>
extern unsigned int min, hr, flag;

void __interrupt() isr(void)
{
    static unsigned int count = 0,mul = 0;
    if(TMR0IF == 1)
    {
        /*TMR0 Register value + 6(offsset count to get 250 ticks) + 2(Instant cycle)*/
        TMR0 = TMR0 + 8;
        count++;
        /*for every 1/2 flag get toggled*/
        if(count == 10000)
        {
            flag = !flag;
        }
        else if(count == 20000)
        {
            count = 0;
            mul++;
            if(mul == 24)
            {
                mul = 0;
                min++;
                
                if(min == 60)
                {
                    min = 0;
                    hr++;
                }
                if(hr>23)
                {
                    hr = 0;
                }
            }
        }
    }
    TMR0IF = 0;
}