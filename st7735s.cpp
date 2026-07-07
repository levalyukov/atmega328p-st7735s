#include "st7735s.hpp"

typedef enum
{
    NOP = 0x00U,
    SWRESET = 0x01U,
    SLPIN = 0x10U,
    SLPOUT = 0x11U,
    GAMSET = 0x26U,
    DISPOFF = 0x28U,
    DISPON = 0x29U,
    MADCTL = 0x36U,
    MADCTL_MX = 0x40U,
    MADCTL_MY = 0x80U,
    MADCTL_MV = 0x20U,
    MADCTL_RGB = 0x08U,
    COLMOD = 0x3AU,
    CASET = 0x2AU,
    RASET = 0x2BU,
    RAMWR = 0x2CU,
    IDMOFF = 0x38U,
    IDMON = 0x39U,
    PTLON = 0x12U,
    NORON = 0x13U
} ST7735S_COMMANDS;

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
    sendData(0x03);

    sendCommand(CASET);
    sendData(0x00);
    sendData(0x00);
    sendData(0x00);
    sendData(ST7735S_WIDTH);

    sendCommand(RASET);
    sendData(0x00);
    sendData(0x00);
    sendData(0x00);
    sendData(ST7735S_HEIGHT);

    sendCommand(IDMOFF);
    sendCommand(SLPOUT);
    sendCommand(PTLON);
    sendCommand(DISPON);
    PORTB |= (1U << chip_select);

    setRotation(0);
}

void ST7735S::setRotation(const unsigned int rotation)
{
    PORTB &= ~(1U << chip_select);
    sendCommand(MADCTL);

    switch (rotation)
    {
    case 1:
        sendData(MADCTL_MY | MADCTL_MX);
        break;

    case 2:
        sendData(0x00);
        break;

    case 3:
        sendData(MADCTL_MY);
        break;

    default:
        sendData(MADCTL_MX);
        break;
    }

    PORTB |= (1U << chip_select);
}

void ST7735S::pixel(const unsigned char x, const unsigned char y,
                    const unsigned short color)
{
    setAddressWindow(x, y, 1, 1);
    PORTB &= ~(1U << chip_select);
    sendData(color);
    PORTB |= (1U << chip_select);
}

void ST7735S::rectangle(const unsigned char x, const unsigned char y,
                        const unsigned char width,
                        const unsigned char height,
                        const unsigned short color)
{
}

void ST7735S::bg(const unsigned short color)
{
    unsigned short x, y;
    setAddressWindow(0, 0, ST7735S_HEIGHT, ST7735S_WIDTH);
    PORTB &= ~(1U << chip_select);
    PORTB |= (1U << data_command);

    for (x = 0; x < ST7735S_HEIGHT; x++)
    {
        for (y = 0; y < ST7735S_HEIGHT; y++)
        {
            spi.transmit(color);
        }
    }

    PORTB |= (1U << chip_select);
}

void ST7735S::end(void)
{
    sendCommand(SWRESET);
    sendCommand(SLPOUT);
    sendCommand(DISPOFF);

    spi.deinit();
    DDRB &= ~((1U << chip_select) | (1U << data_command));
    chip_select = 0U;
    data_command = 0U;
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
    sendData(height);

    sendCommand(RASET);
    sendData(0x00);
    sendData(y);
    sendData(0x00);
    sendData(width);

    sendCommand(RAMWR);
    PORTB |= (1U << chip_select);
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
