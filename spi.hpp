#ifndef _ATMEGA328P_SPI_H
#define _ATMEGA328P_SPI_H

#if defined(__AVR_ATmega328P__)
#  include <avr/io.h>
#  define SCLK (unsigned char)PINB5
#  define MISO (unsigned char)PINB4
#  define MOSI (unsigned char)PINB3
#else
#  error Invalid platform: only ATmega328p
#endif

class SPI
{
public:
  void init(void);
  void transmit(unsigned char data);
  unsigned char receive(unsigned char data);
  void deinit(void);
};

#endif /* _ATMEGA328P_SPI_H */
