
GPIO.H

#ifndef GPIO_H
#define GPIO_H


/* =========================================================
   MACROS
   ========================================================= */

#define  SETIN(n,port)    (port |=  (1<<(n)))
#define  SETOUT(n,port)   (port &= ~(1<<(n)))

#define  SETHIGH(n,port)  (port |=  (1<<(n)))
#define  SETLOW(n,port)   (port &= ~(1<<(n)))
#define  SETTOGGLE(n,port) (port^=(1<<(n)))

/* =========================================================
   TYPE DEFINITIONS
   ========================================================= */

typedef enum
{
    OUTPUT = 0,
    INPUT  = 1
} mode_t;

typedef enum
{
    HIGH = 1,
    LOW  = 0
} state;

typedef enum
{
    PORT_A = 0,
    PORT_B = 1,
    PORT_C = 2,
    PORT_D = 3,
    PORT_E = 4
} port;

typedef struct {
    unsigned char RA0:1;
    unsigned char RA1:1;
    unsigned char RA2:1;
    unsigned char RA3:1;
    unsigned char RA4:1;
    unsigned char RA5:1;
    
} register_a_bits;
typedef struct {
    unsigned char RB0:1;
    unsigned char RB1:1;
    unsigned char RB2:1;
    unsigned char RB3:1;
    unsigned char RB4:1;
    unsigned char RB5:1;
    unsigned char RB6:1;
    unsigned char RB7:1;
 
}  register_b_bits;
typedef struct {
    unsigned char RC0:1;
    unsigned char RC1:1;
    unsigned char RC2:1;
    unsigned char RC3:1;
    unsigned char RC4:1;
    unsigned char RC5:1;
    unsigned char RC6:1;
    unsigned char RC7:1;
 
}  register_c_bits;
typedef struct {
    unsigned char RD0:1;
    unsigned char RD1:1;
    unsigned char RD2:1;
    unsigned char RD3:1;
    unsigned char RD4:1;
    unsigned char RD5:1;
    unsigned char RD6:1;
    unsigned char RD7:1;
 
}register_d_bits;

typedef struct {
    unsigned char RE0:1;
    unsigned char RE1:1;
    unsigned char RE2:1;
   
} register_e_bits;


/* =========================================================
   REGISTER DEFINITIONS
   ========================================================= */

/* PORTA */
#define PORTA (*(volatile unsigned char *)0x05)
#define portabits (*(volatile register_a_bits*)0X05)
#define TRISA (*(volatile unsigned char *)0x85)
#define ADCON1(*(volatile unsigned char *)0x9F)                   /* SET PORTA AS DIGITAL IO PIN */

/* PORTB */
#define PORTB (*(volatile unsigned char *)0x06)
#define portbbits (*(volatile unsigned register_b_bits *)0X06)
#define TRISB (*(volatile unsigned char *)0x86)

/* PORTC */
#define PORTC (*(volatile unsigned char *)0x07)
#define portcbits (*(volatile unsigned register_c_bits * ) 0X07)
#define TRISC (*(volatile unsigned char *)0x87)

/* PORTD */
#define PORTD (*(volatile unsigned char *)0x08)
#define portdbits (*(volatile unsigned register_d_bits * )0X08)
#define TRISD (*(volatile unsigned char *)0x88)

/* PORTE */
#define PORTE (*(volatile unsigned char *)0x09)
#define portebits (*(volatile unsigned register_e_bits *)0X09)
#define TRISE (*(volatile unsigned char *)0x89)

/*SPECIAL FUNCTIONS*/
#define  STATUS       (*(volatile unsigned char *)0x03)
#define OPTIONAL_REG (*(volatile unsigned char *)0x81)


/* =========================================================
   GLOBAL VARIABLES (DEFINED IN .c)
   ========================================================= */

extern volatile uint8_t *port_s[];
extern volatile uint8_t *tris[];

/* =========================================================
   GPIO & PORT FUNCTIONS
   ========================================================= */

void GPIO_pin_mode(uint8_t pin_no, mode_t pin_mode);     // MODE - INPUT OR OUTPUT
void GPIO_pin_write(uint8_t pin_no, state pin_state);     //STATE - HIGH OR LOW
uint8_t  GPIO_pin_read(uint8_t pin_no);           


void port_mode(port port_name, mode_t port_mode);        // MODE - INPUT OR OUTPUT
void port_write(port port_name, state port_state);         //STATE - HIGH OR LOW
uint8_t port_read(port n);                 
#end if
