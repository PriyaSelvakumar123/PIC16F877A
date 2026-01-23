#ifndef GPIO_H
#define GPIO_H
/* ===== MACROS ===== */
#define SETIN(n,port)  (port |=(1 << (n)))
#define SETOUT(n,port) (port &=~(1 << (n)))
#define SETHIGH(n,port) (port |=(1 << (n)))
#define SETLOW(n,port)  (port &=~(1 << (n)))

/* ===== DATA TYPES ===== */
typedef enum
{
    OUTPUT=0,
    INPUT=1
}pinmode_t;
typedef enum
{
    HIGH=1,
    LOW=0
} pinstate;

/* ===== REGISTER DEFINITIONS ===== */
/* PORT A */
#define PORTA (*(volatile unsigned char *)0x05)
#define TRISA (*(volatile unsigned char *)0x85)  
#define ADCON1 (*(volatile unsigned char *)0x9F)

/* PORT B */
#define PORTB (*(volatile unsigned char *)0x06)
#define TRISB (*(volatile unsigned char *)0x86)

/* PORT C */
#define PORTC (*(volatile unsigned char *)0x07)
#define TRISC (*(volatile unsigned char *)0x87)

/* PORT D */
#define PORTD (*(volatile unsigned char *)0x08)
#define TRISD (*(volatile unsigned char *)0x88)

/* PORT E */
#define PORTE (*(volatile unsigned char *)0x09)
#define TRISE (*(volatile unsigned char *)0x89)

/* ===== FUNCTION PROTOTYPES ===== */
void GPIO_pinmode(int a, pinmode_t b);
void GPIO_pinwrite(int a, pinstate b);
#endif
