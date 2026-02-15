#include"gpio.h"
/* =========================================================
   KEYPAD
   ========================================================= */

void keypad_scan_calculator(port keypad,port sevenseg);  //PORT_NAME (KEYPAD),PORT_NAME(SEVEN SEG)

uint_8 keypad_scan_phone(void);                //DEFAULT - PORTB
