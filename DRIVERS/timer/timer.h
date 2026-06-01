#ifndef PIC_TIMERS_H
#define PIC_TIMERS_H

#include <stdint.h>

typedef enum
{
    TIMER0_ID,
    TIMER1_ID,
    TIMER2_ID
} timer_id_t;

extern volatile unsigned int ms_counter;

typedef struct
{
    uint8_t PS0    :1;
    uint8_t PS1    :1;
    uint8_t PS2    :1;
    uint8_t PSA    :1;
    uint8_t T0SE   :1;
    uint8_t T0CS   :1;
    uint8_t INTEDG :1;
    uint8_t RBPU   :1;
} OPTION_REGbits_t;

typedef struct
{
    uint8_t RBIF   :1;
    uint8_t INTF   :1;
    uint8_t TMR0IF :1;
    uint8_t RBIE   :1;
    uint8_t INTE   :1;
    uint8_t TMR0IE :1;
    uint8_t PEIE   :1;
    uint8_t GIE    :1;
} INTCONbits_t;

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

typedef struct
{
    uint8_t TMR1ON  :1;
    uint8_t TMR1CS  :1;
    uint8_t T1SYNC  :1;
    uint8_t T1OSCEN :1;
    uint8_t T1CKPS0 :1;
    uint8_t T1CKPS1 :1;
    uint8_t T1RUN   :1;
    uint8_t unused  :1;
} T1CONbits_t;

typedef struct
{
    uint8_t T2CKPS0 :1;
    uint8_t T2CKPS1 :1;
    uint8_t TMR2ON  :1;
    uint8_t TOUTPS0 :1;
    uint8_t TOUTPS1 :1;
    uint8_t TOUTPS2 :1;
    uint8_t TOUTPS3 :1;
    uint8_t unused  :1;
} T2CONbits_t;

#define TMR0            (*(volatile uint8_t*)0x01)

#define OPTION_REG      (*(volatile uint8_t*)0x81)
#define OPTION_REGbits  (*(volatile OPTION_REGbits_t*)&OPTION_REG)

#define INTCON          (*(volatile uint8_t*)0x0B)
#define INTCONbits      (*(volatile INTCONbits_t*)&INTCON)

#define TMR1L           (*(volatile uint8_t*)0x0E)
#define TMR1H           (*(volatile uint8_t*)0x0F)
#define T1CON           (*(volatile uint8_t*)0x10)
#define T1CONbits       (*(volatile T1CONbits_t*)&T1CON)

#define PIR1            (*(volatile uint8_t*)0x0C)
#define PIR1bits        (*(volatile PIR1bits_t*)&PIR1)

#define PIE1            (*(volatile uint8_t*)0x8C)
#define PIE1bits        (*(volatile PIE1bits_t*)&PIE1)

#define TMR2            (*(volatile uint8_t*)0x11)
#define PR2             (*(volatile uint8_t*)0x92)
#define T2CON           (*(volatile uint8_t*)0x12)
#define T2CONbits       (*(volatile T2CONbits_t*)&T2CON)

#define MAX_TASKS 5

void TIMER_Init(timer_id_t id);
void TIMER_Start(timer_id_t id);
void TIMER_Stop(timer_id_t id);
void TIMER_Reset(timer_id_t id);

void delay_ms(uint16_t time);
void delay_us(uint16_t time);

void Scheduler_Init(void);
void NON_BLOCKING(uint16_t delay, void (*func)(void));

#endif
