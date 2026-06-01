#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* MACROS */
#define SETIN(n, port)       ((port) |=  (1U << (n)))
#define SETOUT(n, port)      ((port) &= ~(1U << (n)))

#define SETHIGH(n, port)     ((port) |=  (1U << (n)))
#define SETLOW(n, port)      ((port) &= ~(1U << (n)))
#define SETTOGGLE(n, port)   ((port) ^=  (1U << (n)))

/* TYPE DEFINITIONS */
typedef enum
{
    GPIO_OUTPUT = 0,
    GPIO_INPUT  = 1
} gpio_mode_t;

typedef enum
{
    LOW  = 0,
    HIGH = 1
} state_t;

typedef enum
{
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} port_t;

/* REGISTER BIT STRUCTURES */
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
} register_b_bits;

typedef struct {
    unsigned char RC0:1;
    unsigned char RC1:1;
    unsigned char RC2:1;
    unsigned char RC3:1;
    unsigned char RC4:1;
    unsigned char RC5:1;
    unsigned char RC6:1;
    unsigned char RC7:1;
} register_c_bits;

typedef struct {
    unsigned char RD0:1;
    unsigned char RD1:1;
    unsigned char RD2:1;
    unsigned char RD3:1;
    unsigned char RD4:1;
    unsigned char RD5:1;
    unsigned char RD6:1;
    unsigned char RD7:1;
} register_d_bits;

typedef struct {
    unsigned char RE0:1;
    unsigned char RE1:1;
    unsigned char RE2:1;
} register_e_bits;

/* REGISTER DEFINITIONS */
#define PORTA   (*(volatile uint8_t *)0x05)
#define TRISA   (*(volatile uint8_t *)0x85)
#define ADCON1  (*(volatile uint8_t *)0x9F)

#define PORTB   (*(volatile uint8_t *)0x06)
#define TRISB   (*(volatile uint8_t *)0x86)

#define PORTC   (*(volatile uint8_t *)0x07)
#define TRISC   (*(volatile uint8_t *)0x87)

#define PORTD   (*(volatile uint8_t *)0x08)
#define TRISD   (*(volatile uint8_t *)0x88)

#define PORTE   (*(volatile uint8_t *)0x09)
#define TRISE   (*(volatile uint8_t *)0x89)

#define portabits (*(volatile register_a_bits *)0x05)
#define portbbits (*(volatile register_b_bits *)0x06)
#define portcbits (*(volatile register_c_bits *)0x07)
#define portdbits (*(volatile register_d_bits *)0x08)
#define portebits (*(volatile register_e_bits *)0x09)

/* SPECIAL FUNCTION REGISTERS */
#define STATUS       (*(volatile uint8_t *)0x03)
#define OPTION_REG   (*(volatile uint8_t *)0x81)

/* GLOBAL VARIABLES */
extern volatile uint8_t *port_s[];
extern volatile uint8_t *tris[];

/* FUNCTION PROTOTYPES */
void GPIO_pin_mode(uint8_t pin_no, gpio_mode_t pin_mode);
void GPIO_pin_write(uint8_t pin_no, state_t pin_state);
uint8_t GPIO_pin_read(uint8_t pin_no);

void port_mode(port_t port_name, gpio_mode_t port_mode);
void port_write(port_t port_name, state_t port_state);
uint8_t port_read(port_t port_name);

#endif
