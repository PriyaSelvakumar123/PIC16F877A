#include "gpio.h"

void GPIO_pinmode(int a,pinmode_t b)
{
    if(a>=33&&a<=40)                    //PORTB PINS
    {
        if(b==OUTPUT)
            SETOUT(a-33,TRISB);
        else
            SETIN(a-33,TRISB);
    }
    else if(a>=2&&a<=7)                 //PORTA PINS
    {
        ADCON1=0x06;
        if(b==OUTPUT)
            SETOUT(a-2,TRISA);
        else
            SETIN(a-2,TRISA);
    }
    else if((a>14&&a<19)||(a>22&&a<27)) //PORTC PINS
    {
        if(a<19)a=a-15;
        else a=a-19;

        if(b==OUTPUT)
            SETOUT(a,TRISC);
        else
            SETIN(a,TRISC);
    }
    else if((a>18&&a<23)||(a>26&&a<31))  //PORTD PINS
    {
        if(a<23)a=a-19;
        else a=a-23;

        if(b==OUTPUT)
            SETOUT(a,TRISD);
        else
            SETIN(a,TRISD);
    }
    else if(a>7&&a<11)                 //PORTE PINS
    {
        ADCON1=0x06;
        if(b==OUTPUT)
            SETOUT(a-8,TRISE);
        else
            SETIN(a-8,TRISE);
    }
}

void GPIO_pinwrite(int a,pinstate b)
{
    if(a>=33&&a<=40)
    {
        if(b==LOW)
            SETLOW(a-33,PORTB);
        else
            SETHIGH(a-33,PORTB);
    }
    else if(a>=2&&a<=7)
    {
        if(b==LOW)
            SETLOW(a-2,PORTA);
        else
            SETHIGH(a-2,PORTA);
    }
    else if((a>14&&a<19)||(a>22&&a<27))
    {
        if(a<19)a=a-15;
        else a=a-19;

        if(b==LOW)
            SETLOW(a,PORTC);
        else
            SETHIGH(a,PORTC);
    }
    else if((a>18&&a<23)||(a>26&&a<31))
    {
        if(a<23)a=a-19;
        else a=a-23;

        if(b==LOW)
            SETLOW(a,PORTD);
        else
            SETHIGH(a,PORTD);
    }
    else if(a>7&&a<11)
    {
        if(b==LOW)
            SETLOW(a-8,PORTE);
        else
            SETHIGH(a-8,PORTE);
    }
}

void seven_segment(unsigned char a,port n)        //COMMON CATHODE - PRINT HEX VALUE (0 - F)
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
      *m =hex_digits[i];
    }
    else if(i>=10&&i<16)
    {
        *m =hex_digits[i];
    } 
    return;
}

void dot_alphabet(const unsigned char a,port n1,port n2 )
{
    
   volatile unsigned char *port[] = { &PORTA,&PORTB,&PORTC,&PORTD,&PORTE };
   volatile unsigned char *tris[] = { &TRISA,&TRISB,&TRISC,&TRISD,&TRISE };
   volatile unsigned char *p1,*p2,*t1,*t2;
   p1=port[n1];
   p2=port[n2];
   t1=tris[n1];
   t2=tris[n2];
   *t1=0x00;
   *t2=0x00;

   volatile unsigned char i1 = a -'A';
   const unsigned char alphabet[26][8] =
{
/* A */ {0x00,0x3C,0x66,0x66,0x7E,0x66,0x66,0x66},
/* B */ {0x00,0x78,0x48,0x48,0x70,0x48,0x48,0x78},
/* C */ {0x00,0x1E,0x20,0x40,0x40,0x40,0x20,0x1E},
/* D */ {0x00,0x38,0x24,0x22,0x22,0x24,0x38,0x00},
/* E */ {0x00,0x3C,0x20,0x38,0x20,0x20,0x3C,0x00},
/* F */ {0x00,0x3C,0x20,0x38,0x20,0x20,0x20,0x00},
/* G */ {0x00,0x3E,0x20,0x20,0x2E,0x22,0x3E,0x00},
/* H */ {0x00,0x24,0x24,0x3C,0x24,0x24,0x24,0x00},
/* I */ {0x00,0x38,0x10,0x10,0x10,0x10,0x38,0x00},
/* J */ {0x00,0x1C,0x08,0x08,0x08,0x28,0x38,0x00},
/* K */ {0x00,0x24,0x28,0x30,0x28,0x24,0x24,0x00},
/* L */ {0x00,0x20,0x20,0x20,0x20,0x20,0x3C,0x00},
/* M */ {0x00,0x44,0xAA,0x92,0x82,0x82,0x00,0x00},
/* N */ {0x00,0x22,0x32,0x2A,0x26,0x22,0x00,0x00},
/* O */ {0x00,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00},
/* P */ {0x00,0x38,0x24,0x24,0x38,0x20,0x20,0x00},
/* Q */ {0x00,0x3C,0x42,0x42,0x46,0x3E,0x01,0x00},
/* R */ {0x00,0x38,0x24,0x24,0x38,0x24,0x24,0x00},
/* S */ {0x00,0x3C,0x20,0x3C,0x04,0x04,0x3C,0x00},
/* T */ {0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x00},
/* U */ {0x00,0x42,0x42,0x42,0x42,0x24,0x18,0x00},
/* V */ {0x00,0x22,0x22,0x22,0x14,0x14,0x08,0x00},
/* W */ {0x00,0x82,0x92,0x54,0x54,0x28,0x00,0x00},
/* X */ {0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00},
/* Y */ {0x00,0x44,0x28,0x10,0x10,0x10,0x10,0x00},
/* Z */ {0x00,0x3C,0x04,0x08,0x10,0x20,0x3C,0x00}
};
    
    unsigned char col[8] = {
        0xFE,0xFD,0xFB,0xF7,
        0xEF,0xDF,0xBF,0x7F
    };

   
           for(unsigned char k=0; k<50; k++) 
            {
                for(unsigned char i=0; i<8; i++)
                {
                    *p1 =  col[i];             // column select
                    *p2 = alphabet[i1][i];    // row data
                    __delay_ms(0.2);
                }
             }
        
}

