#include "timers.h"

volatile unsigned int ms_counter = 0;

static uint16_t task_delay[MAX_TASKS];
static uint16_t task_counter[MAX_TASKS];
static void (*task_function[MAX_TASKS])(void);
static unsigned char taskIndex = 0;

void TIMER_Init(timer_id_t id)
{
    if(id == TIMER0_ID)
    {
        OPTION_REGbits.T0CS = 0;
        OPTION_REGbits.PSA  = 0;
        TMR0 = 0;
        INTCONbits.TMR0IF = 0;
    }
    else if(id == TIMER1_ID)
    {
        T1CONbits.TMR1CS = 0;
        T1CONbits.TMR1ON = 0;
        TMR1H = 0;
        TMR1L = 0;
        PIR1bits.TMR1IF = 0;
    }
    else if(id == TIMER2_ID)
    {
        T2CONbits.TMR2ON = 0;
        TMR2 = 0;
        PIR1bits.TMR2IF = 0;
    }
}

void TIMER_Start(timer_id_t id)
{
    switch(id)
    {
        case TIMER0_ID:
            OPTION_REGbits.PSA = 0;
            break;

        case TIMER1_ID:
            T1CONbits.TMR1ON = 1;
            break;

        case TIMER2_ID:
            T2CONbits.TMR2ON = 1;
            break;
    }
}

void TIMER_Stop(timer_id_t id)
{
    switch(id)
    {
        case TIMER0_ID:
            OPTION_REGbits.PSA = 1;
            break;

        case TIMER1_ID:
            T1CONbits.TMR1ON = 0;
            break;

        case TIMER2_ID:
            T2CONbits.TMR2ON = 0;
            break;
    }
}

void TIMER_Reset(timer_id_t id)
{
    switch(id)
    {
        case TIMER0_ID:
            TMR0 = 0;
            break;

        case TIMER1_ID:
            TMR1H = 0;
            TMR1L = 0;
            break;

        case TIMER2_ID:
            TMR2 = 0;
            break;
    }
}

void delay_ms(uint16_t time)
{
    uint32_t total_counts;
    uint16_t overflows;
    uint8_t preload;

    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 0;

    TMR0 = 0;
    INTCONbits.TMR0IF = 0;

    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;

    total_counts = ((uint32_t)time * 1000UL * 5) / 256;
    overflows = total_counts / 256;
    preload = 256 - (total_counts % 256);

    TMR0 = preload;
    INTCONbits.TMR0IF = 0;

    while(!INTCONbits.TMR0IF);

    INTCONbits.TMR0IF = 0;

    while(overflows--)
    {
        TMR0 = 0;

        while(!INTCONbits.TMR0IF);

        INTCONbits.TMR0IF = 0;
    }
}

static void TIMER1_Init(void)
{
    T1CONbits.TMR1CS = 0;
    TMR1H = 0xEC;
    TMR1L = 0x78;
}

static void TIMER1_Start(void)
{
    T1CONbits.TMR1ON = 1;
}

static void TIMER1_InterruptEnable(void)
{
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE  = 1;
}

void Scheduler_Init(void)
{
    int i;

    for(i = 0; i < MAX_TASKS; i++)
    {
        task_function[i] = 0;
    }

    TIMER1_Init();
    TIMER1_InterruptEnable();
    TIMER1_Start();
}

void NON_BLOCKING(uint16_t delay, void (*func)(void))
{
    if(taskIndex < MAX_TASKS)
    {
        task_delay[taskIndex] = delay;
        task_counter[taskIndex] = 0;
        task_function[taskIndex] = func;
        taskIndex++;
    }
}

void __interrupt() ISR()
{
    if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;

        TMR1H = 0xEC;
        TMR1L = 0x78;

        for(unsigned char i = 0; i < MAX_TASKS; i++)
        {
            if(task_function[i] != 0)
            {
                task_counter[i]++;

                if(task_counter[i] >= task_delay[i])
                {
                    task_counter[i] = 0;
                    task_function[i]();
                }
            }
        }
    }
}


void delay_us(uint16_t time)
{
    uint16_t total_counts;
    uint8_t overflows;
    uint8_t preload;

    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 1;

    TMR0 = 0;
    INTCONbits.TMR0IF = 0;

    total_counts = time * 5;
    overflows = total_counts / 256;
    preload = 256 - (total_counts % 256);

    TMR0 = preload;
    INTCONbits.TMR0IF = 0;

    while(!INTCONbits.TMR0IF);

    INTCONbits.TMR0IF = 0;

    while(overflows--)
    {
        TMR0 = 0;

        while(!INTCONbits.TMR0IF);

        INTCONbits.TMR0IF = 0;
    }
}
