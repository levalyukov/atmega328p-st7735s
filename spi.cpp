#include "spi.hpp"

void SPI::init(void)
{
  DDRB |= ((1U << SCLK) | (1U << MOSI));
  DDRB &= ~(1U << MISO);
  SPCR &= ~(1U << SPI2X);
  SPCR |= ((1U << MSTR) | (1U << SPR0));
  SPCR |= (1U << SPE);
}

void SPI::transmit(const unsigned char data)
{
  SPDR = data;
  while (!(SPSR & (1U << SPIF)));
}

unsigned char SPI::receive(const unsigned char data)
{
  SPDR = data;
  while (!(SPSR & (1U << SPIF)));
  return (unsigned char)SPDR;
}

void SPI::deinit(void)
{
  DDRB &= ~((1U << SCLK) | (1U << MOSI));
  SPCR &= ~((1U << SPE) | (1U << MSTR) | (1U << SPR1) | (1U << SPR0));
}
