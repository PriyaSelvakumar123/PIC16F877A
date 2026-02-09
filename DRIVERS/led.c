#include"gpio.h"

void led_blink(int pin)
{
    GPIO_pin_mode(pin,INPUT);

    while(1)
    {
        pin_write(pin,HIGH);
        __delay_ms(500);

        pin_write(pin,LOW);
        __delay_ms(500);
    }
}
