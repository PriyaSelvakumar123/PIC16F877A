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

📁 File Structure

GPIO_Driver/
│
├── gpio.h
├── gpio.c
└── README.md

📌 APIs
GPIO_pinmode(int pin,pinmode_t mode);
GPIO_pinwrite(int pin,pinstate state);

🧠 Reference

Microcontroller: PIC16F877A
Manufacturer: Microchip Technology Inc.
Document: PIC16F87XA Datasheet
