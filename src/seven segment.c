#include "gpio.h"

/* =========================================================
   SEVEN SEGMENT DRIVER
   ========================================================= */

void seven_segment_ANODE(uint_8 a, port n)
{
    volatile uint_8 *port_arr[] = { &PORTA, &PORTB, &PORTC, &PORTD, &PORTE };
    volatile uint_8 *tris_arr[] = { &TRISA, &TRISB, &TRISC, &TRISD, &TRISE };
    volatile uint_8 *m, *t;

    const uint_8 seg[16] = {
        0xC0, 0xF9, 0xA4, 0xB0,
        0x99, 0x92, 0x82, 0xF8,
        0x80, 0x90, 0x88, 0x83,
        0xC6, 0xA1, 0x86, 0x8E
    };

    m = port_arr[n];
    t = tris_arr[n];
    *t = 0x00;

    uint_8 i = 0;

    if(a >= '0' && a <= '9') i = a - '0';
    else if(a >= 'A' && a <= 'F') i = a - 'A' + 10;

    *m = seg[i];
}

void seven_segment_CATHODE(uint_8 a, port n)
{
    volatile uint_8 *port_arr[] = { &PORTA, &PORTB, &PORTC, &PORTD, &PORTE };
    volatile uint_8 *tris_arr[] = { &TRISA, &TRISB, &TRISC, &TRISD, &TRISE };
    volatile uint_8 *m, *t;

    const uint_8 hex_digits[16] = {
        0x3F, 0x06, 0x5B, 0x4F,
        0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C,
        0x39, 0x5E, 0x79, 0x71
    };

    m = port_arr[n];
    t = tris_arr[n];
    *t = 0x00;

    uint_8 i = 0;

    if(a >= '0' && a <= '9') i = a - '0';
    else if(a >= 'A' && a <= 'F') i = a - 'A' + 10;

    *m = hex_digits[i];
}

void four_digit_segment(uint_16 num, port seg, port mux)
{
    volatile uint_8 *p_seg, *p_mux, *t_seg, *t_mux;

    const uint_8 segs[10] = {
        0xC0, 0xF9, 0xA4, 0xB0,
        0x99, 0x92, 0x82, 0xF8,
        0x80, 0x90
    };

    const uint_8 mux_val[4] = { 0x08, 0x04, 0x02, 0x01 }; // Rightmost → leftmost

    t_seg = tris[seg];
    p_seg = port_s[seg];
    t_mux = tris[mux];
    p_mux = port_s[mux];

    *t_seg = 0x00;  // Segment port as output
    *t_mux = 0x00;  // MUX port as output

    uint_8 digits[4];
    digits[0] = num % 10;
    digits[1] = (num / 10) % 10;
    digits[2] = (num / 100) % 10;
    digits[3] = num / 1000;

    for(uint_8 i = 0; i < 4; i++)
    {
        *p_mux = 0x00;        // Disable all digits
        *p_seg = segs[digits[i]]; // Load segment data
        *p_mux = mux_val[i];  // Enable digit
        __delay_us(300);
    }
}
