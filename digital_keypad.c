#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void) {
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode) {
    static unsigned char once = 1;
    static unsigned char pre_key;
    static unsigned char longpress;
        if (mode == LEVEL_DETECTION)
        {
            return KEYPAD_PORT & INPUT_LINES;
        }
        else
        {
            if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
            {
                once = 0;
                longpress=0;
                pre_key=KEYPAD_PORT & INPUT_LINES;
            
                //return KEYPAD_PORT & INPUT_LINES;
            }
            else if (!once && (pre_key ==(KEYPAD_PORT & INPUT_LINES)) && longpress <50)
            {
                longpress++;
            }
            else if(longpress==50)
            {
                longpress++;
                return 0X80 | pre_key;
            }
            else if((KEYPAD_PORT & INPUT_LINES)==ALL_RELEASED && !once)
            {
                once=1;
                if(longpress<50){
                    return pre_key;
                }
            }
        }


    return ALL_RELEASED;
    
}

