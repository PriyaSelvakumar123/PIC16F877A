#include "i2c.h"

void i2c_delay(void)               // 5u sec
{
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 1;

    TMR0 = 231;
    INTCONbits.TMR0IF = 0;

    while(!INTCONbits.TMR0IF);

    INTCONbits.TMR0IF = 0;
}

void scl_high(void)
{
    TRISB |= (1 << SCL_PIN);     // release SCL
}

void scl_low(void)
{
    PORTB &= ~(1 << SCL_PIN);
    TRISB &= ~(1 << SCL_PIN);    // drive low
}

void sda_high(void)
{
    TRISB |= (1 << SDA_PIN);     // release SDA
}

void sda_low(void)
{
    PORTB &= ~(1 << SDA_PIN);
    TRISB &= ~(1 << SDA_PIN);    // drive low
}

void I2C_init(void)
{
    ADCON1 = 0x07;   // all pins digital

    sda_high();
    scl_high();
}

void I2C_start(void)
{
    sda_high();
    scl_high();
    i2c_delay();

    sda_low();
    i2c_delay();

    scl_low();
    i2c_delay();
}

void I2C_stop(void)
{
    sda_low();
    i2c_delay();

    scl_high();
    i2c_delay();

    sda_high();
    i2c_delay();
}

unsigned char I2C_write_byte(unsigned char data)
{
    unsigned char i;
    unsigned char ack;

    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)
            sda_high();
        else
            sda_low();

        i2c_delay();

        scl_high();
        i2c_delay();

        scl_low();
        i2c_delay();

        data <<= 1;
    }

    sda_high();      // release SDA for ACK
    i2c_delay();

    scl_high();
    i2c_delay();

    ack = (PORTB >> SDA_PIN) & 1;

    scl_low();
    i2c_delay();

    return ack;      // 0 = ACK, 1 = NACK
}

void I2C_writechar(unsigned char address, unsigned char data)
{
    I2C_start();

    I2C_write_byte(address << 1);
    I2C_write_byte(data);

    I2C_stop();
}

void I2C_writestring(unsigned char address, char *data)
{
    I2C_start();

    if(I2C_write_byte(address << 1))
    {
        I2C_stop();
        return;
    }

    while(*data)
    {
        if(I2C_write_byte(*data++))
        {
            I2C_stop();
            return;
        }
    }

    I2C_stop();
}
