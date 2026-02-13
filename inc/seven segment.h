#include"gpio.h"

/* =========================================================
   SEVEN SEGMENT
   ========================================================= */

void seven_segment_ANODE(unsigned char a, port n);      // HEX - 0 - F , PORT_NAME (SEVEN SEG)

void seven_segment_CATHODE(unsigned char a, port n);

void four_digit_segment(unsigned int num, port seg, port mux);   // DEC 0 - 9 ,PORT_NAME (SEVEN SEG) ,PORT_NAME (SELECT LINE - 4)

