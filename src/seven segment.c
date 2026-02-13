#include "gpio.h"

/* =========================================================
   SEVEN SEGMENT
   ========================================================= */

void seven_segment_ANODE(unsigned char a,port n)
{
   volatile unsigned char *port[] = { &PORTA,&PORTB,&PORTC,&PORTD,&PORTE };
   volatile unsigned char *tris[] = { &TRISA,&TRISB,&TRISC,&TRISD,&TRISE };
   volatile unsigned char *m,*t;

unsigned char seg[16] = {
0xC0,0xF9,0xA4,0xB0,
0x99,0x92,0x82,0xF8,
0x80,0x90,0x88,0x83,
0xC6,0xA1,0x86,0x8E
};

    m = port[n];
    t=tris[n];
    *t=0X00;
    int i;
    if (a >= '0' && a <= '9')
    i = a - '0';
    else if (a >= 'A' && a <= 'F')
    i = a - 'A' + 10;

    if(i>=0&& i<=9)
    {
      *m =seg[i];
    }
    else if(i>=10&&i<16)
    {
        *m =seg[i];
    } 
    return;
}

void seven_segment_CATHODE(unsigned char a,port n)
{
   volatile unsigned char *port[] = { &PORTA,&PORTB,&PORTC,&PORTD,&PORTE };
   volatile unsigned char *tris[] = { &TRISA,&TRISB,&TRISC,&TRISD,&TRISE };
   volatile unsigned char *m,*t;

unsigned char hex_digits[16] = {
    0x3F, 0x06, 0x5B, 0x4F,
    0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x77, 0x7C,
    0x39, 0x5E, 0x79, 0x71
};

    m = port_s[n];
    t=tris[n];
    *t=0X00;
    int i;
    if (a >= '0' && a <= '9')
    i = a - '0';
    else if (a >= 'A' && a <= 'F')
    i = a - 'A' + 10;

    if(i>=0&& i<=9)
    {
      *m =hex_digits[i];
    }
    else if(i>=10&&i<16)
    {
        *m =hex_digits[i];
    } 
    return;
}

void four_digit_segment(unsigned int num,port n,port m)
{
    volatile unsigned char *t1,*p1,*t2,*p2;
unsigned char segs[10] =
{
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

unsigned char mux[4] =
{
    0x08, // rightmost
    0x04,
    0x02,
    0x01  // leftmost
};

t1=tris[n];
p1=port_s[n];
t2=tris[m];
p2=port_s[m];
*t1 = 0x00;
*t2= 0x00;

    unsigned char d[4];

    d[0] = num%10;
    d[1] = (num/10) % 10;
    d[2] = (num/100) % 10;
    d[3] = num/1000;

    for(unsigned char i = 0; i < 4; i++)
    {
        *p2 = 0x00;          // disable all digits
        *p1 = segs[d[i]];     // segment data
        *p2 = mux[i];        // enable digit
        __delay_us(300);
    }
}


