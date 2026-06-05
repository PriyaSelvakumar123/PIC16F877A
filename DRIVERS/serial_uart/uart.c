#include "uart.h"

void UART_Init(uint32_t baudrate)
{
    SPBRG = (_XTAL_FREQ / (16UL * baudrate)) - 1;

    TXSTAbits.SYNC = 0;    //Asynchronous
    TXSTAbits.BRGH = 1;    //HIGH SPEED

    RCSTAbits.SPEN = 1;    //serial port RC6 AND RC7 

    TXSTAbits.TXEN = 1;    //TRANSMITER ENABLE
    RCSTAbits.CREN = 1;    //RECIVER ENABLE
}

void UART_WriteChar(char data)
{
    while(!PIR1bits.TXIF);
    TXREG = data;
}

char UART_Read(void)
{
    while(!PIR1bits.RCIF);
    return RCREG;
}

void UART_WriteString(const char *str)
{
    while(*str)
    {
        UART_WriteChar(*str);
        str++;
    }
}

void main()
{
    UART_Init(9600);

    while(1)
    {
        UART_WriteString("SUJAN..\n\r");
    }
}
