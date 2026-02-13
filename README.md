GPIO Driver – PIC16F877A ⭐

A GPIO driver for PIC16F877A developed using pure register-level programming, without using any built-in header libraries,

• follows Microchip datasheet register mapping

• uses direct TRISx and PORTx control

• designed for learning, reuse, and real hardware testing

🔧 Features

✔ Controls PORTA–PORTE

✔ TRISx & PORTx register based

✔ INPUT / OUTPUT configuration

✔ Digital HIGH / LOW control

✔ ADC disabled using ADCON1 where required

✔ Displays hexadecimal characters on a seven-segment display

✔ Displays a single uppercase alphabet character on an 8×8 LED dot matrix

📁 File Structure

GPIO_Driver

├── gpio.h       // GPIO macros, data types, register definitions
│

├── gpio.c       // GPIO driver implementation
│

├── led.c       // seven segment driver implementation
│

├── seven_segment.c       // seven segment driver implementation
│

├── keypad.c       // keypad driver implementation
│

├── dotmatrix.c       // dotmatrix driver implementation
│

└── README.md    // Project documentation

PROJECT - GPIO

├── APPLICATION CODE/PROJECT
│
└── README.md    // Project documentation

📌 APIs

void GPIO_pin_mode(int a, mode_t b);
void GPIO_pin_write(int a, state b);
int  GPIO_pin_read(int a);

void port_mode(port n, mode_t m);
void port_write(port n, state m);
int  port_read(port n);

void seven_segment_ANODE(unsigned char a, port n);
void seven_segment_CATHODE(unsigned char a, port n);
void four_digit_segment(unsigned int num, port seg, port mux);

void keypad_scan_calculator(port n,port m);
char keypad_scan_phone(void);

void dot_alphabet(const unsigned char a, port n1, port n2);

🧠 Reference  

Microcontroller: PIC16F877A

Manufacturer: Microchip Technology Inc.

Document: PIC16F87XA Datasheet - https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf
