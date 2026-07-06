#include <avr/io.h>
#include <util/delay.h>
#include "st7735s.hpp"

#define CS (unsigned char)PINB2
#define DC (unsigned char)PINB1

int main(void)
{ 
  ST7735S display;
  display.begin(CS,DC);
  display.bgFill(ST7735S_BLACK); 
  
  return 0;
}
