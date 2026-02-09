#include "gpio.h"



/* =========================================================
   GLOBAL VARIABLES (DEFINED IN .c)
   ========================================================= */
void GPIO_pin_mode(int a,mode_t b)
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

void GPIO_pin_write(int a,state b)
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

int pin_read(int a)
{
    if(a >=33 && a <= 40)
    {
        return(PORTB &(1 << (a - 33)))? 1 : 0;
    }
    else if(a>=2 && a<=7)
    {
        return(PORTA & (1<<(a - 2)))?1 : 0;
    }
    else if(((a>14) && (a<19)) || ((a>22) && (a<27)))
    {
        if(a<19)
            a = a - 15;
        else
            a = a - 19;

        return (PORTC & (1 << a)) ? 1 : 0;
    }
    else if(((a>18) && (a<23)) || ((a>26) && (a<31)))
    {
        if(a < 23)
            a = a - 19;
        else
            a = a - 23;
        return (PORTD & (1 << a)) ? 1 : 0;
    }
    else if((a>7) && (a<11))
    {
        return (PORTE & (1 << (a - 8))) ? 1 : 0;
    }
    return 0;
}


/* =========================================================
   GPIO & PORT FUNCTIONS
   ========================================================= */

void port_mode(port n,mode_t m)
{
    volatile unsigned char *t1;
    t1 = tris[n];
    if(m== INPUT)
    {
        *t1=0xFF;
    }
    if(m == OUTPUT)
    {
        *t1=0x00;
    }
}

void port_write(port n,state m)
{
    volatile unsigned char *p1;
    p1 = port_s[n];
    if(m== HIGH)
    {
        *p1=0xFF;
    }
    if(m == LOW)
    {
        *p1=0x00;
    }
}

int port_read(port n)
{
    if(n & 0xFF)
        return 1;
    else if(n & 0x00 )
        return 0;

}


