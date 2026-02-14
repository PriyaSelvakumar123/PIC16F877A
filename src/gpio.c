#include "gpio.h"
#include <stdint.h>

/* =========================================================
   GLOBAL ARRAY DEFINITIONS
   ========================================================= */

volatile uint8_t *port_registers[] =
{
    &PORTA,
    &PORTB,
    &PORTC,
    &PORTD,
    &PORTE
};

volatile uint8_t *tris_registers[] =
{
    &TRISA,
    &TRISB,
    &TRISC,
    &TRISD,
    &TRISE
};

/* =========================================================
   GPIO PIN MODE FUNCTION
   ========================================================= */

void GPIO_pin_mode(uint8_t pin_number, mode_t pin_mode)       
{
   
    if(pin_number >= 2 && pin_number <= 7)                    // PORTA
    {
        ADCON1 = 0x06;                                        // ADCON1 USED FOR PORTE AS DIGITAL INPUT OR OUTPUT


        if(pin_mode==OUTPUT)
            SETOUT(pin_number - 2,TRISA);
        else
            SETIN(pin_number - 2,TRISA);
    }
    else if(pin_number >= 33 && pin_number <= 40)            // PORTB               
    {
        if(pin_mode==OUTPUT)
            SETOUT(pin_number - 33,TRISB);
        else
            SETIN(pin_number - 33,TRISB);
    }

    else if((pin_number > 14 && pin_number < 19) ||         // PORTC
            (pin_number > 22 && pin_number < 27))
    {
        uint8_t bit;
       
        if(pin_number < 19)
            bit = pin_number - 15;
        else
            bit = pin_number - 19;

        if(pin_mode == OUTPUT)
            SETOUT(bit,TRISC);
        else
            SETIN(bit,TRISC);
    }

    else if((pin_number > 18 && pin_number < 23) ||       // PORTD
            (pin_number > 26 && pin_number < 31))
    {
        uint8_t bit;

        if(pin_number < 23)
            bit = pin_number - 19;
        else
            bit = pin_number - 23;

        if(pin_mode == OUTPUT)
            SETOUT(bit,TRISD);
        else
            SETIN(bit,TRISD);
    }

    else if(pin_number > 7 && pin_number < 11)         // PORTE
    {
        ADCON1 = 0x06;                                 // ADCON1 USED FOR PORTE AS DIGITAL INPUT OR OUTPUT

        if(pin_mode == OUTPUT)
            SETOUT(pin_number - 8, TRISE);
        else
            SETIN(pin_number - 8, TRISE);
    }
}

/* =========================================================
   GPIO PIN WRITE FUNCTION
   ========================================================= */

void GPIO_pin_write(uint8_t pin_number, state pin_state)
{
    if(pin_number >= 33 && pin_number <= 40)
    {
        if(pin_state == LOW)
            SETLOW(pin_number - 33, PORTB);
        else
            SETHIGH(pin_number - 33, PORTB);
    }

    else if(pin_number >= 2 && pin_number <= 7)
    {
        if(pin_state == LOW)
            SETLOW(pin_number - 2, PORTA);
        else
            SETHIGH(pin_number - 2, PORTA);
    }

    else if((pin_number > 14 && pin_number < 19) ||
            (pin_number > 22 && pin_number < 27))
    {
        uint8_t bit;

        if(pin_number < 19)
            bit = pin_number - 15;
        else
            bit = pin_number - 19;

        if(pin_state == LOW)
            SETLOW(bit, PORTC);
        else
            SETHIGH(bit, PORTC);
    }

    else if((pin_number > 18 && pin_number < 23) ||
            (pin_number > 26 && pin_number < 31))
    {
        uint8_t bit;

        if(pin_number < 23)
            bit = pin_number - 19;
        else
            bit = pin_number - 23;

        if(pin_state == LOW)
            SETLOW(bit, PORTD);
        else
            SETHIGH(bit, PORTD);
    }

    else if(pin_number > 7 && pin_number < 11)
    {
        if(pin_state == LOW)
            SETLOW(pin_number - 8, PORTE);
        else
            SETHIGH(pin_number - 8, PORTE);
    }
}

/* =========================================================
   GPIO PIN READ FUNCTION
   ========================================================= */

uint8_t GPIO_pin_read(uint8_t pin_number)
{
    if(pin_number >= 33 && pin_number <= 40)
        return (PORTB & (1 << (pin_number - 33))) ? 1 : 0;

    else if(pin_number >= 2 && pin_number <= 7)
        return (PORTA & (1 << (pin_number - 2))) ? 1 : 0;

    else if((pin_number > 14 && pin_number < 19) ||
            (pin_number > 22 && pin_number < 27))
    {
        uint8_t bit;

        if(pin_number < 19)
            bit = pin_number - 15;
        else
            bit = pin_number - 19;

        return (PORTC & (1 << bit)) ? 1 : 0;
    }

    else if((pin_number > 18 && pin_number < 23) ||
            (pin_number > 26 && pin_number < 31))
    {
        uint8_t bit;

        if(pin_number < 23)
            bit = pin_number - 19;
        else
            bit = pin_number - 23;

        return (PORTD & (1 << bit)) ? 1 : 0;
    }

    else if(pin_number > 7 && pin_number < 11)
        return (PORTE & (1 << (pin_number - 8))) ? 1 : 0;

    return 0;
}

/* =========================================================
   PORT FUNCTIONS
   ========================================================= */

void port_mode(port port_name, mode_t port_mode)
{
    volatile uint8_t *tris_register = tris_registers[port_name];

    if(port_mode == INPUT)
        *tris_register = 0xFF;
    else
        *tris_register = 0x00;
}

void port_write(port port_name, state port_state)
{
    volatile uint8_t *port_register = port_registers[port_name];

    if(port_state == HIGH)
        *port_register = 0xFF;
    else
        *port_register = 0x00;
}

uint8_t port_read(port port_name)
{
    volatile uint8_t *port_register = port_registers[port_name];

    return *port_register;
}
