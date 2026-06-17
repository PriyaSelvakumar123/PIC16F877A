# PIC16F877A Driver Library

⭐ **A high-performance register-level peripheral driver library for the Microchip PIC16F877A microcontroller.**

Developed using bare-metal register-level programming and software bit-banging techniques, this library provides modular and reusable drivers for PIC16F877A peripherals. It demonstrates a strong understanding of microcontroller architecture, communication protocols, hardware interfacing, and low-level embedded firmware development.


---

# 🔧 Features

### GPIO Driver

* Full support for PORTA, PORTB, PORTC, PORTD, and PORTE.
* Pin-level and port-level configuration.
* Direct TRISx and PORTx register manipulation.
* ADCON1 digital I/O configuration support.

### I2C Driver

* Hardware MSSP-based I2C communication.
* Master mode support.
* EEPROM and sensor interfacing.

### I2C Bit-Banging Driver

* Software-based I2C implementation.
* No hardware MSSP dependency.
* Flexible GPIO-based communication.

### UART Driver

* Hardware UART communication.
* Configurable baud rate.
* TX and RX support.

### UART Bit-Banging Driver

* Software serial communication.
* Useful when hardware UART is unavailable.

### Timer Driver

* Timer0 support.
* Timer1 support.
* Timer2 support.
* Delay and timing applications.

### Middleware Components

* Seven Segment Display Driver.
* 8×8 LED Dot Matrix Driver.
* 4×4 Keypad Driver.
* LED Driver.

---

# 📁 Project Structure

```text
PIC16F877A-DriverLibrary/

├── DRIVERS
│
│   ├── GPIO
│   │   ├── gpio.c
│   │   └── gpio.h
│   │
│   ├── I2C
│   │   ├── i2c.c
│   │   └── i2c.h
│   │
│   ├── I2C_BitBanging
│   │   ├── i2c_bitbanging.c
│   │   └── i2c_bitbanging.h
│   │
│   ├── UART
│   │   ├── uart.c
│   │   └── uart.h
│   │
│   ├── UART_BitBanging
│   │   ├── uart_bitbanging.c
│   │   └── uart_bitbanging.h
│   │
│   └── TIMER
│       ├── timer.c
│       └── timer.h
│
├── MIDDLEWARE
│   ├── sevensegment
│   ├── dotmatrix
│   ├── keypad
│   └── led
│
├── EXAMPLE_CODES
│
├── PROJECTS
│
├── EXAMPLES
│
└── README.md
```

---

# 📌 GPIO API Reference

| Function                                            | Description                        |
| --------------------------------------------------- | ---------------------------------- |
| `void GPIO_pin_mode(uint8_t pin, mode_t mode)`      | Configure a pin as INPUT or OUTPUT |
| `void GPIO_pin_write(uint8_t pin, state pin_state)` | Write HIGH or LOW to a pin         |
| `uint8_t GPIO_pin_read(uint8_t pin)`                | Read pin state                     |
| `void port_mode(port port_name, mode_t mode)`       | Configure an entire port           |

---

# 📌 Middleware API Reference

| Function                                                 | Description                                         |
| -------------------------------------------------------- | --------------------------------------------------- |
| `seven_segment_ANODE(uint8_t value, port p)`             | Display hexadecimal value on Common Anode display   |
| `seven_segment_CATHODE(uint8_t value, port p)`           | Display hexadecimal value on Common Cathode display |
| `uint8_t keypad_scan_phone(void)`                        | Scan keypad and return pressed key                  |
| `dot_alphabet(uint8_t ch, port row_port, port col_port)` | Display alphabet on 8×8 LED matrix                  |

---

# ⚠️ Critical Hardware Notes

# GPIO 

## ADCON1 Register Configuration

PIC16F877A powers up with PORTA and PORTE configured as analog inputs.

To use them as digital GPIO:

```c
ADCON1 = 0x06;
```

or

```c
ADCON1 = 0x07;
```

This disables analog functionality and enables proper digital I/O operation.

---

## RA4 Open-Drain Output

RA4 behaves differently from other GPIO pins.

### Characteristics

* Can actively drive LOW.
* Cannot actively drive HIGH.

### Requirement

Use an external pull-up resistor:

```text
RA4 ---- 10kΩ ---- +5V
```

Without a pull-up resistor, RA4 may not operate correctly as a digital output.

---

## PORTB Internal Pull-Ups

The keypad driver enables internal weak pull-ups:

```c
OPTION_REG &= ~(1 << 7);
```

Benefits:

* Eliminates external pull-up resistors.
* Reduces hardware complexity.
* Simplifies keypad interfacing.

##PROTOCALS

##I2C

⚠️ I2C Pull-Up Resistors

The I2C bus uses open-drain/open-collector outputs for both SDA and SCL lines. Therefore, the PIC16F877A cannot drive these lines HIGH directly.

📚 Requirement: External pull-up resistors must be connected to both SDA and SCL lines.

Typical Connection:

+5V
 │
 ├── 4.7kΩ ── SDA
 │
 └── 4.7kΩ ── SCL
---

# 🧠 Technical Specifications

| Parameter                   | Value       |
| --------------------------- | ----------- |
| Microcontroller             | PIC16F877A  |
| Architecture                | 8-bit PIC   |
| Compiler                    | XC8         |
| IDE                         | MPLAB X IDE |
| Simulator                   | Proteus     |
| Debugger                    | PICkit 3    |
| Recommended Clock Frequency | 20 MHz      |

---

# 📂 Example Applications

### Example Codes

* GPIO Testing
* UART Communication
* I2C EEPROM Interface
* Timer Delay Applications
* Seven Segment Counter

### Projects

* Lift Controller System
* Digital Counter
* Display Interface Projects
* Sensor Interfacing Projects

---

# 📚 Datasheet

PIC16F877A Datasheet

https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf

---

# 👨‍💻 Author

**PRIYA DHARSHINI S**

Electronics and Communication Engineering (ECE)

Embedded Systems | Firmware Development | Microcontroller Programming

---

# ⚖️ License

This project is open-source and may be used, modified, and distributed for:

* Educational purposes
* Research projects
* Embedded systems learning
* Commercial hardware testing

Contributions, bug reports, and feature requests are welcome.
