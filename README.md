GPIO Driver Library – PIC16F877A 

⭐A high-performance, register-level GPIO driver library for the Microchip PIC16F877A microcontroller.


Developed using pure register-level programming (bypassing standard built-in header libraries where possible) to provide deep control over hardware and minimize overhead.


🔧 FeaturesFull Port Control: 

        Comprehensive support for PORTA through PORTE.
        
Register-Based: 

        Direct manipulation of TRISx and PORTx registers.
        
ADC Management:

        Automatic disabling of analog functions via ADCON1 for digital I/O stability.
        
Seven-Segment Support: 

        Dedicated APIs for Common Anode/Cathode displays (Hexadecimal support).
        
Matrix & Keypad:

        Integrated drivers for 8x8 LED Dot Matrices and 4x4 Keypad scanning (Phone/Calculator layouts).
        
Learning Centric:

        Ideal for students and engineers transitiong from library-dependency to bare-metal firmware development.


📁 Project StructurePlaintextPIC16F877A-DriverLibrary/

PIC16F877A-DriverLibrary/

├── inc/                        # Header files

│   ├── gpio.h              

│   ├── display.h           

│   └── keypad.h           

├── src/                        # Implementation files

│   ├── gpio.c             

│   ├── led.c               

│   ├── seven_segment.c     

│   ├── keypad.c            

│   └── dotmatrix.c         

├── examples/              

│   ├── LIFT_System.c       

│   └── counters.c          

└── README.md                  # Project documentation


📌 Core API Reference

GPIO Control
         
         Function                                          Description
         

    void GPIO_pin_mode(int pin, mode_t m)    -  Sets a specific physical pin to INPUT or OUTPUT.


    void GPIO_pin_write(int pin, state s)     -  Writes HIGH (1) or LOW (0) to a specific pin.


    int GPIO_pin_read(int pin)               -  Returns the current digital state of a pin.


    void port_mode(port n, mode_t m)         -  Configures an entire port (A-E) at once.


    void GPIO_pin_mode(int pin, mode_t m)      -  Sets a specific physical pin to INPUT or OUTPUT.


⚠️ Critical Hardware Notes for GPIO

The ADCON1 Register

On the PIC16F877A, PORTA and PORTE pins are multiplexed with Analog-to-Digital Converter (ADC) inputs. On power-up, they default to Analog mode.

  📚  Fix: To use them as digital GPIO, you must set ADCON1 = 0x06 (or 0x07). This switches          the  pins to Digital mode so your TRIS settings actually take effect.
    
The Open-Drain Pin (RA4)

Pin RA4 is unique. It is an Open-Drain output.

  📚  Behavior: It can pull a signal to Ground (LOW), but it cannot pull it to VCC (HIGH) on         its own.
  
  📚  Requirement: You must use an external pull-up resistor (typically 10k ohm) if you want         to use RA4 as a digital output.
  
PORTB Pull-ups

  📚  Your keypad.c driver uses OPTION_REG &= ~(1<<7). This enables internal weak pull-up             resistors on PORTB. This is a great hardware-saving feature that eliminates the need for        8 external resistors when connecting a keypad.


Peripherals

        Function                                              Description

        
"seven_segment_ANODE(char a, port n)"      -   Displays Hex char (0-F) on Common Anode segment.

"seven_segment_CATHODE(char a, port n)"    -   Displays Hex char (0-F) on Common Cathode segment.

"keypad_scan_phone()"                      -   Scans a 4x3/4x4 keypad and returns the char pressed.

"dot_alphabet(char a, port n1, port n2)"   -   Renders an uppercase letter on an 8x8 LED Matrix.


🧠 Technical ReferenceMicrocontroller:

PIC16F877AClock Frequency: Recommended 20MHz (Standard for __delay_ms)

Compiler       : XC8 (MPLAB X IDE)

simulator      : PROTEUS  

Debugging tool : PIC it3

Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf

⚖️ License

This project is open-source. Feel free to use, modify, and distribute for educational and 

commercial hardware testing.
