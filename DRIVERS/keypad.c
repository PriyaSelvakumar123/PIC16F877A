#include "gpio.h"

/* =========================================================
   KEYPAD
   ========================================================= */

void keypad_scan(port n)
{   
    volatile unsigned char *t,*p;
     unsigned char keyboard[4][4] = 
     {
        {'7','8','9','A'},
        {'4','5','6','B'},
        {'1','2','3','C'},
        {'F','0','E','D'}
     };
   
        t = tris[n] ;
        p = port_s[n];
        *t = 0xF0;
        *p = 0x0F;
       
            for(int i=0;i<4;i++)
     {
          *p =(char)(1<<i);
          
          if((*p & (1<<4)))
          {
            seven_segment(keyboard[i][0],1); 
          }
          
          else if((*p & (1<<5)))
          {
               seven_segment(keyboard[i][1],1); 
          }
           
            else if((*p & (1<<6)))
          {
               seven_segment(keyboard[i][2],1);
               
          }  
          else if((*p&(1<<7)))
          {
               seven_segment(keyboard[i][3],1);
          }  
          
     }
   
}
