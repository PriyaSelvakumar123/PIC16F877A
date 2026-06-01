#include"led.h"

void led_blink(int pin)
{
    GPIO_pin_mode(pin,OUTPUT);

    while(1)
    {
        pin_write(pin,HIGH);
        __delay_ms(10);

        pin_write(pin,LOW);
        __delay_ms(10);
    }
}

