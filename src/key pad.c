#include "gpio.h"
#include"keypad.h"

/* =========================================================
   KEYPAD
   ========================================================= */

void keypad_scan(port n, port m)
{
    volatile uint_8 *t, *p;
    uint_8 keyboard[4][4] =
    {
        {'7','8','9','A'},
        {'4','5','6','B'},
        {'1','2','3','C'},
        {'F','0','E','D'}
    };

    t = tris[n];
    p = port_s[n];

    *t = 0xF0;     // Upper nibble input (columns)
    *p = 0x0F;     // Lower nibble output HIGH (rows)

    for(uint_8 i = 0; i < 4; i++)
    {
        *p = 0x0F;          // All rows HIGH
        *p &= ~(1 << i);    // Make one row LOW

        __delay_us(200);    // Debounce delay

        if(!(*p & (1<<4)))
            seven_segment(keyboard[i][0], m);

        else if(!(*p & (1<<5)))
            seven_segment(keyboard[i][1], m);

        else if(!(*p & (1<<6)))
            seven_segment(keyboard[i][2], m);

        else if(!(*p & (1<<7)))
            seven_segment(keyboard[i][3], m);
    }
}

uint_8 keypad_scan_phone(void)
{
    uint_8 row;

    uint_8 keymap[4][3] =
    {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
    };

    TRISB = 0b01110000;     // RB0–RB3 output, RB4–RB6 input
    OPTION_REGbits.nRBPU = 0;  // Enable PORTB pull-ups

    for(row = 0; row < 4; row++)
    {
        PORTB = 0x0F;           // All rows HIGH
        PORTB &= ~(1 << row);   // One row LOW

        __delay_us(200);

        if(!(PORTB & (1<<4))) { while(!(PORTB & (1<<4))); return keymap[row][0]; }
        if(!(PORTB & (1<<5))) { while(!(PORTB & (1<<5))); return keymap[row][1]; }
        if(!(PORTB & (1<<6))) { while(!(PORTB & (1<<6))); return keymap[row][2]; }
    }

    return 0;   // No key pressed
}

