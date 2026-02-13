#include "gpio.h"

/* =========================================================
   KEYPAD
   ========================================================= */

void keypad_scan(port n,port m)
{   volatile unsigned char *t,*p;
    unsigned int bit1=-1,bit2=-1;
     unsigned char keyboard[4][4] = 
     {
        {'7','8','9','A'},
        {'4','5','6','B'},
        {'1','2','3','C'},
        {'F','0','E','D'}
     };
        t = tris[n];
        p = port_s[n];
                
   
        *t = 0xF0;
        *p = 0x0F;
       
            for(int i=0;i<4;i++)
     {
          *p=(char)(1<<i);
          
          if((*p & (1<<4)))
          {
            seven_segment(keyboard[i][0],m); 
          }
          
          else if((*p & (1<<5)))
          {
               seven_segment(keyboard[i][1],m); 
          }
           
            else if((*p & (1<<6)))
          {
               seven_segment(keyboard[i][2],m);
               
          }  
          else if((*p &(1<<7)))
          {
               seven_segment(keyboard[i][3],m);
          }  
          
     }
}

char keypad_scan_phone(void)
{
    unsigned char row;
    unsigned char keymap[4][3] =
    {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
    };

    TRISB = 0b01110000;
    OPTION_REG &= ~(1<<7);    // Enable PORTB pull-ups

    PORTB = 0x0F;             // All rows HIGH

    for(row = 0; row < 4; row++)
    {
        PORTB = 0x0F & ~(1 << row);   // One row LOW
        __delay_us(200);               // Debounce

        if(!(PORTB & (1<<4))) return keymap[row][0];
        if(!(PORTB & (1<<5))) return keymap[row][1];
        if(!(PORTB & (1<<6))) return keymap[row][2];
    }

    return 0;   // No key pressed
}


