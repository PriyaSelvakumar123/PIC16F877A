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
