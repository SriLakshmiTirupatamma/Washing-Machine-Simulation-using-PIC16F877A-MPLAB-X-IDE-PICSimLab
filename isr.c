#include <xc.h>
#include "main.h"
extern unsigned char sec,min;
void __interrupt() isr(void)
{
    static unsigned int count=0;
    if(TMR2IF==1)
    {
        if( ++count == 1250) // 250 , 200ns 8 bit timer for 1 sec
        {
            count = 0;
            if(sec>0)
            {
                sec--;
            }
            else if(sec==0 && min>0)
            {
                min--;
                sec=59;
           
        }
        }
        
        TMR2IF = 0; // clear interrupt flag 
        
    }
    
    
}

