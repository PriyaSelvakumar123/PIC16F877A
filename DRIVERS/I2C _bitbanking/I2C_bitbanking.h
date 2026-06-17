#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include "gpio.h"
#include "timer.h"

#define _XTAL_FREQ 20000000UL

#define SCL_PIN 0   // RB0
#define SDA_PIN 1   // RB1

void I2C_init(void);
void I2C_start(void);                   
void I2C_stop(void);

void scl_high(void);
void scl_low(void);
void sda_high(void);
void sda_low(void);

unsigned char I2C_write_byte(unsigned char data);
void I2C_writechar(unsigned char address, unsigned char data);
void I2C_writestring(unsigned char address, char *data);

#endif
