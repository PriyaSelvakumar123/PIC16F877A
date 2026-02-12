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

GPIO_Driver/

├── gpio.h       // GPIO macros, data types, register definitions
│

├── gpio.c       // GPIO driver implementation
│

└── README.md    // Project documentation

📌 APIs

GPIO_pinmode(int pin,pinmode_t mode);

GPIO_pinwrite(int pin,pinstate state);

void seven_segment(unsigned char a,port n);

void dot_alphabet(const unsigned char a,port n1,port n2 );

🧠 Reference  

Microcontroller: PIC16F877A

Manufacturer: Microchip Technology Inc.

Document: PIC16F87XA Datasheet - https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf
