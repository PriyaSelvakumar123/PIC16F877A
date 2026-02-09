#ifndef GPIO_H
#define GPIO_H

#include <xc.h>

/* =========================================================
   MACROS
   ========================================================= */

#define  SETIN(n,port)    (port |=  (1<<(n)))
#define  SETOUT(n,port)   (port &= ~(1<<(n)))

#define  SETHIGH(n,port)  (port |=  (1<<(n)))
#define  SETLOW(n,port)   (port &= ~(1<<(n)))

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

/* =========================================================
   REGISTER DEFINITIONS
   ========================================================= */

/* PORTA */
#define PORTA (*(volatile unsigned char *)0x05)
#define TRISA (*(volatile unsigned char *)0x85)
#define ADCON1(*(volatile unsigned char *)0x9F)

/* PORTB */
#define PORTB (*(volatile unsigned char *)0x06)
#define TRISB (*(volatile unsigned char *)0x86)

/* PORTC */
#define PORTC (*(volatile unsigned char *)0x07)
#define TRISC (*(volatile unsigned char *)0x87)

/* PORTD */
#define PORTD (*(volatile unsigned char *)0x08)
#define TRISD (*(volatile unsigned char *)0x88)

/* PORTE */
#define PORTE (*(volatile unsigned char *)0x09)
#define TRISE (*(volatile unsigned char *)0x89)

/*SPECIAL FUNCTIONS*/
#define STATUS       (*(volatile unsigned char *)0x03)
#define OPTIONAL_REG (*(volatile unsigned char *)0x81)


/* =========================================================
   GLOBAL VARIABLES (DEFINED IN .c)
   ========================================================= */

extern volatile unsigned char *port_s[];
extern volatile unsigned char *tris[];

/* =========================================================
   GPIO & PORT FUNCTIONS
   ========================================================= */

void GPIO_pin_mode(int a, mode_t b);
void GPIO_pin_write(int a, state b);
int  GPIO_pin_read(int a);

void port_mode(port n, mode_t m);
void port_write(port n, state m);
int  port_read(port n);


/* =========================================================
   SEVEN SEGMENT
   ========================================================= */

void seven_segment_ANODE(unsigned char a, port n);
void seven_segment_CATHODE(unsigned char a, port n);
void four_digit_segment(unsigned int num, port seg, port mux);

/* =========================================================
   KEYPAD
   ========================================================= */

void keypad_scan(port n,port m);

/* =========================================================
   DOT MATRIX
   ========================================================= */

void dot_alphabet(const unsigned char a, port n1, port n2);
void scroll_top_to_bottom(unsigned char ch, port n1, port n2);

#endif
