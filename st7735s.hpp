#ifndef ST7735S_H
#define ST7735S_H

#if defined(__AVR_ATmega328P__)
#  include <avr/io.h>
#  include <util/delay.h>
#  include "spi.hpp"

#  define ST7735S_HEIGHT 160
#  define ST7735S_WIDTH  80
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
  void bgFill(unsigned short color);
  void end(void);

private:
  SPI spi;
  typedef enum
  {
    NOP     = 0x00U,
    SWRESET = 0x01U,
    SLPIN   = 0x10U,
    SLPOUT  = 0x11U,
    GAMSET  = 0x26U,
    DISPOFF = 0x28U,
    DISPON  = 0x29U,
    MADCTL  = 0x36U,
    COLMOD  = 0x3AU,
    CASET   = 0x2AU,
    RASET   = 0x2BU,
    RAMWR   = 0x2CU,
    IDMOFF  = 0x38U,
    IDMON   = 0x39U
  } st7735s_t;
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
