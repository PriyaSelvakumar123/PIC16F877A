#include <stdint.h>
#include "gpio.h"

#ifndef I2C_H
#define I2C_H

#define _XTAL_FREQ 20000000UL


//    STRUCTURES   //
typedef struct 
{
  uint8_t BF : 1;     // SSPBUF STATUS READ/WRITE
  uint8_t UA : 1;
  uint8_t RW : 1;
  uint8_t S  : 1;
  uint8_t P  : 1;
  uint8_t DA : 1;    // DATA OR ADDERSS
  uint8_t CKE : 1;
  uint8_t SMP : 1;   // SLEW RATE CONTROL BITS
}SSPSTATbits_t;

typedef struct 
{
  uint8_t SSPM0 : 1;    //1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
  uint8_t SSPM1 : 1;
  uint8_t SSPM2 : 1;
  uint8_t SSPM3 : 1;
  uint8_t CKP   : 1;
  uint8_t SSPEN : 1;    
  uint8_t SSPOV : 1;
  uint8_t WCOL  : 1;
}SSPCON1bits_t;

typedef struct 
{
  uint8_t SEN    : 1;    //1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
  uint8_t RSEN   : 1;
  uint8_t PEN    : 1;
  uint8_t RCEN   : 1;
  uint8_t ACKEN  : 1;
  uint8_t ACKDT  : 1;    
  uint8_t ACKSTAT: 1;
  uint8_t GCEN   : 1;
}SSPCON2bits_t;

typedef struct
{
    uint8_t TMR1IF :1;
    uint8_t TMR2IF :1;
    uint8_t CCP1IF :1;
    uint8_t SSPIF  :1;   // START ACKNOLEDGEMENT
    uint8_t TXIF   :1;
    uint8_t RCIF   :1;
    uint8_t ADIF   :1;
    uint8_t PSPIF  :1;
} PIR1bits_t;

typedef struct
{
    uint8_t TMR1IE :1;
    uint8_t TMR2IE :1;
    uint8_t CCP1IE :1;
    uint8_t SSPIE  :1;
    uint8_t TXIE   :1;
    uint8_t RCIE   :1;
    uint8_t ADIE   :1;
    uint8_t PSPIE  :1;
} PIE1bits_t;


   //  REGISTERS   //

#define SSPBUF      (*(volatile uint8_t*)0x13)

#define SSPCON1     (*(volatile uint8_t*)0x14)
#define SSPCON1bits (*(volatile SSPCON1bits_t*)0x14)

#define SSPCON2     (*(volatile uint8_t*)0x91)
#define SSPCON2bits (*(volatile SSPCON2bits_t*)0x91)

#define SSPADD      (*(volatile uint8_t*)0x93)

#define SSPSTAT     (*(volatile uint8_t*)0x94)
#define SSPSTATbits (*(volatile SSPSTATbits_t*)0x94)

#define PIR1        (*(volatile uint8_t*)0x0C)
#define PIR1bits    (*(volatile PIR1bits_t*)0x0C)

#define PIE1        (*(volatile uint8_t*)0x8C)
#define PIE1bits    (*(volatile PIE1bits_t*)0x8C)


void I2C_Init(void);

void I2C_Start(void);
void I2C_Stop(void);

void I2C_Write(uint8_t Address , uint8_t *data);
uint8_t I2C_Read(uint8_t Address);

#endif

