#ifndef UART_H
#define UART_H

#include <stdint.h>

#define _XTAL_FREQ 20000000UL

typedef struct
{
    uint8_t TX9 :1;
    uint8_t TRMT:1;
    uint8_t BRGH :1;
    uint8_t SENDB:1;
    uint8_t SYNC :1;
    uint8_t TXEN :1;
    uint8_t TX9D:1;
    uint8_t CSRC :1;
} TXSTAbits_t;


typedef struct
{
    uint8_t RX9  :1;
    uint8_t OERR :1;
    uint8_t FERR :1;
    uint8_t ADDEN:1;
    uint8_t CREN :1;
    uint8_t SREN :1;
    uint8_t RX9D :1;
    uint8_t SPEN :1;
} RCSTAbits_t;

typedef struct
{
    uint8_t TMR1IF :1;
    uint8_t TMR2IF :1;
    uint8_t CCP1IF :1;
    uint8_t SSPIF  :1;
    uint8_t TXIF   :1;
    uint8_t RCIF   :1;
    uint8_t ADIF   :1;
    uint8_t PSPIF  :1;
} PIR1bits_t;

#define TXSTA     (*(volatile uint8_t*)0x98)
#define TXSTAbits (*(volatile TXSTAbits_t*)&TXSTA)

#define RCSTA     (*(volatile uint8_t*)0x18)
#define RCSTAbits (*(volatile RCSTAbits_t*)&RCSTA)

#define SPBRG     (*(volatile uint8_t*)0x99)
#define TXREG     (*(volatile uint8_t*)0x19)
#define RCREG     (*(volatile uint8_t*)0x1A)

#define PIR1      (*(volatile uint8_t*)0x0C)
#define PIR1bits  (*(volatile PIR1bits_t*)&PIR1)

void UART_Init(uint32_t baudrate);
void UART_WriteChar(char data);
char UART_Read(void);
void UART_WriteString(const char *str);

#endif
