#include "gpio.h"

/* GLOBAL ARRAY DEFINITIONS */
volatile uint8_t *port_s[] =
{
    &PORTA,
    &PORTB,
    &PORTC,
    &PORTD,
    &PORTE
};
volatile uint8_t *tris[] =
{
    &TRISA,
    &TRISB,
    &TRISC,
    &TRISD,
    &TRISE
};

/* GPIO PIN MODE */
void GPIO_pin_mode(uint8_t pin_number, gpio_mode_t pin_mode)
{
    uint8_t bit;

    if(pin_number >=2 && pin_number <=7)          // PORTA
    {
        ADCON1 = 0x06;
        bit = pin_number - 2;

        if(pin_mode == GPIO_OUTPUT)
            SETOUT(bit, TRISA);
        else
            SETIN(bit, TRISA);
    }

    else if(pin_number >= 33 && pin_number <= 40)   // PORTB
    {
        bit = pin_number-33;

        if(pin_mode == GPIO_OUTPUT)
            SETOUT(bit, TRISB);
        else
            SETIN(bit, TRISB);
    }

    else if((pin_number >= 15 && pin_number <= 18) ||
            (pin_number >= 23 && pin_number <= 26)) // PORTC
    {
        if(pin_number <= 18)
            bit = pin_number-15;
        else
            bit = pin_number-19;

        if(pin_mode == GPIO_OUTPUT)
            SETOUT(bit, TRISC);
        else
            SETIN(bit, TRISC);
    }

    else if((pin_number >= 19 && pin_number <= 22) ||
            (pin_number >= 27 && pin_number <= 30)) // PORTD
    {
        if(pin_number <= 22)
            bit = pin_number - 19;
        else
            bit = pin_number - 23;

        if(pin_mode == GPIO_OUTPUT)
            SETOUT(bit, TRISD);
        else
            SETIN(bit, TRISD);
    }

    else if(pin_number >= 8 && pin_number <= 10)    // PORTE
    {
        ADCON1 = 0x06;
        bit = pin_number - 8;

        if(pin_mode == GPIO_OUTPUT)
            SETOUT(bit, TRISE);
        else
            SETIN(bit, TRISE);
    }
}

/* GPIO PIN WRITE */
void GPIO_pin_write(uint8_t pin_number, state_t pin_state)
{
    uint8_t bit;

    if(pin_number >= 2 && pin_number <= 7)          // PORTA
    {
        bit = pin_number - 2;

        if(pin_state == HIGH)
            SETHIGH(bit, PORTA);
        else
            SETLOW(bit, PORTA);
    }

    else if(pin_number >= 33 && pin_number <= 40)   // PORTB
    {
        bit = pin_number - 33;

        if(pin_state == HIGH)
            SETHIGH(bit, PORTB);
        else
            SETLOW(bit, PORTB);
    }

    else if((pin_number >= 15 && pin_number <= 18) ||
            (pin_number >= 23 && pin_number <= 26)) // PORTC
    {
        if(pin_number <= 18)
            bit = pin_number - 15;
        else
            bit = pin_number - 19;

        if(pin_state == HIGH)
            SETHIGH(bit, PORTC);
        else
            SETLOW(bit, PORTC);
    }

    else if((pin_number >= 19 && pin_number <= 22) ||
            (pin_number >= 27 && pin_number <= 30)) // PORTD
    {
        if(pin_number <= 22)
            bit = pin_number - 19;
        else
            bit = pin_number - 23;

        if(pin_state == HIGH)
            SETHIGH(bit, PORTD);
        else
            SETLOW(bit, PORTD);
    }

    else if(pin_number >= 8 && pin_number <= 10)    // PORTE
    {
        bit = pin_number - 8;

        if(pin_state == HIGH)
            SETHIGH(bit, PORTE);
        else
            SETLOW(bit, PORTE);
    }
}

/* GPIO PIN READ */
uint8_t GPIO_pin_read(uint8_t pin_number)
{
    uint8_t bit;

    if(pin_number >= 2 && pin_number <= 7)
    {
        bit = pin_number - 2;
        return (PORTA & (1U << bit)) ? 1 : 0;
    }

    else if(pin_number >= 33 && pin_number <= 40)
    {
        bit = pin_number - 33;
        return (PORTB & (1U << bit)) ? 1 : 0;
    }

    else if((pin_number >= 15 && pin_number <= 18) ||
            (pin_number >= 23 && pin_number <= 26))
    {
        if(pin_number <= 18)
            bit = pin_number - 15;
        else
            bit = pin_number - 19;

        return (PORTC & (1U << bit)) ? 1 : 0;
    }

    else if((pin_number >= 19 && pin_number <= 22) ||
            (pin_number >= 27 && pin_number <= 30))
    {
        if(pin_number <= 22)
            bit = pin_number - 19;
        else
            bit = pin_number - 23;

        return (PORTD & (1U << bit)) ? 1 : 0;
    }

    else if(pin_number >= 8 && pin_number <= 10)
    {
        bit = pin_number - 8;
        return (PORTE & (1U << bit)) ? 1 : 0;
    }

    return 0;
}

/* PORT MODE */
void port_mode(port_t port_name, gpio_mode_t port_mode)
{
    if(port_name > PORT_E)
        return;

    if(port_mode == GPIO_INPUT)
        *tris[port_name] = 0xFF;
    else
        *tris[port_name] = 0x00;
}

/* PORT WRITE */
void port_write(port_t port_name, state_t port_state)
{
    if(port_name > PORT_E)
        return;

    if(port_state == HIGH)
        *port_s[port_name] = 0xFF;
    else
        *port_s[port_name] = 0x00;
}

/* PORT READ */
uint8_t port_read(port_t port_name)
{
    if(port_name > PORT_E)
        return 0;

    return *port_s[port_name];
}
