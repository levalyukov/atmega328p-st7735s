#include "st7735s.hpp"
#include <avr/io.h>
#include <util/delay.h>

#define CS (unsigned char)PINB2
#define DC (unsigned char)PINB1

int main(void)
{
    ST7735S display;
    display.begin(CS, DC);
    display.bg(ST7735S_BLACK);
    return 0;
}
