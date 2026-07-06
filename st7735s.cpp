#include "st7735s.hpp"

void ST7735S::begin(const unsigned char cs, const unsigned char dc)
{
  chip_select = cs;
  data_command = dc;
  DDRB |= ((1U << chip_select) | (1U << data_command));
  PORTB |= (1U << chip_select);

  PORTC &= ~(1U << PINC6);
  _delay_ms(120);
  PORTC |= (1U << PINC6);

  spi.init();

  PORTB &= ~(1U << chip_select);
  sendCommand(SWRESET);
  sendCommand(GAMSET);
  sendCommand(COLMOD);
  sendCommand(MADCTL);
  sendCommand(IDMOFF);
  sendCommand(SLPOUT);
  sendCommand(DISPON);
  PORTB |= (1U << chip_select);
}

void ST7735S::setAddressWindow(const unsigned char x,
			       const unsigned char y,
			       const unsigned char width,
			       const unsigned char height)
{
  PORTB &= ~(1U << chip_select);
  sendCommand(CASET);
  sendData(0x00);
  sendData(x);
  sendData(0x00);
  sendData(width);

  sendCommand(RASET);
  sendData(0x00);
  sendData(y);
  sendData(0x00);
  sendData(height);
  
  sendCommand(RAMWR);
  PORTB |= (1U << chip_select);
}

void ST7735S::bgFill(unsigned short color)
{
  unsigned short x,y;
  
  setAddressWindow(0,0,ST7735S_WIDTH,ST7735S_HEIGHT/2);
  PORTB &= ~(1U << chip_select);
  PORTB |= (1U << data_command);
  for (x = 0; x < ST7735S_HEIGHT; x++)
    {
      for (y = 0; y < ST7735S_WIDTH; y++)
	{
	  spi.transmit(color);
	}
    }
  PORTB |= (1U << chip_select);
}

void ST7735S::end(void)
{
  sendCommand((unsigned char)SWRESET);
  sendCommand((unsigned char)SLPOUT);
  sendCommand((unsigned char)DISPOFF);
  
  spi.deinit();
  DDRB &= ~((1U << chip_select) | (1U << data_command));
  chip_select = 0U;
  data_command = 0U;
}

void ST7735S::sendData(const unsigned char data)
{
  PORTB |= (1U << data_command);
  spi.transmit(data);
}

void ST7735S::sendCommand(const unsigned char command)
{
  PORTB &= ~(1U << data_command);
  spi.transmit(command);
}
