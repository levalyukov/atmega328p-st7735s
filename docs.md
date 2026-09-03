# Библиотека для ST7735S контроллера

Попытка написать библиотеку для дисплеев на базе контроллера ST7735S.

Важная оговорка: библиотека пишется для китайского дисплея, который имеет очень странный контроллер ST7735S и по даташиту не соответствует действительности, поэтому в коде имеются буквально костыльные решения.

Для работы был использован [официальный даташит от производителя.](www.alldatasheet.com/datasheet-pdf/pdf/1775164/SITRONIX/ST7735S.html)

## Сборка и компиляция

Проект был написан под чистый AVR и на unix-подобной ОС, поэтому здесь используется Makefile. Чуть позже я добавлю раздел как подключить библиотеку к Arduino. Для компиляции вам необходимо иметь Makefile на своем компьютере.

### Основные цели Makefile

**Компиляция, сборка, конвертирование в ihex формат и прошивка МК:**

```bash
make
```

**Сборка .cpp файлов проекта:**

```bash
make build
```

**Только прошивка МК готового ihx-файла:**

```bash
make flash
```

**Проверка на синтаксические ошибки:**

```bash
make syntax
```

**Форматирование кода:**

```bash
make format
```

**Очистить временные и объектные файлы:**

```bash
make clean
```

## Методы SPI модуля

Инициализация SPI-интерфейса:

```cpp
void SPI::init(void);
```

Отправка данных в 8-битном формате:

```cpp
void SPI::transmit(const unsigned char data);
```

Отправка данных и чтение ответа в 8-битном формате:

```cpp
unsigned char SPI::receive(const unsigned char data);
```

Отключить SPI-интерфейс:

```cpp
void SPI::deinit(void);
```

## Методы SPI модуля

Инициализировать дисплей:

```cpp
void begin(unsigned char cs, unsigned char dc);
```

Установить расположение дисплея:

```cpp
void setRotation(unsigned int rotation);
```

Отключить дисплей:

```cpp
void end(void);
```

Вывести пиксель на дисплей:

```cpp
void pixel(unsigned char x, unsigned char y, unsigned short color);
```

Залить фон:

```cpp
void bg(unsigned short color);
```

**Пример кода:**

```cpp
#include <st7735s.hpp>

#define CS PINB2
#define DC PINB1

int main(void)
{
    ST7735S display;
    display.begin(cs, dc);
    display.bg(ST7735S_BLACK);
}
```
