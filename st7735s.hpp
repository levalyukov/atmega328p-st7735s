#ifndef ST7735S_H
#define ST7735S_H

#if defined(__AVR_ATmega328P__)
#  include <avr/io.h>
#  include <util/delay.h>
#  include "spi.hpp"

#  define ST7735S_OFFSET 26
#  define ST7735S_HEIGHT 160+ST7735S_OFFSET
#  define ST7735S_WIDTH  80+ST7735S_OFFSET
#  define ST7735S_BLACK  0x0000
#  define ST7735S_WHITE  0xFFFF
#  define ST7735S_RED    0xF800
#  define ST7735S_GREEN  0x07E0
#  define ST7735S_BLUE   0x00F1
#  define ST7735S_YELLOW 0xFFE0
#else
#  error Invalid platform: only ATmega328p.
#endif

class ST7735S
{
public:    
  void begin(unsigned char cs, unsigned char dc);
  void setRotation(unsigned int rotation);
  void end(void);
  
  /* -------
   * Graphic
   * ------- */
  void pixel(unsigned char x, unsigned char y, unsigned short color);
  void bg(unsigned short color);
  void rectangle(unsigned char x,
		 unsigned char y,
		 unsigned char width,
		 unsigned char height,
		 unsigned short color);

private:
  SPI spi;
  unsigned char chip_select = 0U;
  unsigned char data_command = 0U;

  void sendData(unsigned char data);
  void sendCommand(unsigned char command);
  void setAddressWindow(unsigned char x,
			unsigned char y,
			unsigned char width,
			unsigned char height);
};

#endif /* ST7735S_H */
