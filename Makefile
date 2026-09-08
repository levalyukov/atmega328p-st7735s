uploader	:= avrdude
device		:= atmega328p
bootloader	:= arduino
baudrate	:= 115200
port		:= /dev/tty.usbserial-140 # <- Обязательно измените порт / Changing the port is required
clock		:= 1000000UL

library		:= st7735s.hpp
compilier	:= avr-gcc
flags		:= -mmcu=${device} -std=c++17 -pedantic -Wall -D F_CPU=${clock} -Os -I ${library}
output		:= firmware
sources		:= ${wildcard *.cpp}
objects		:= ${sources:.cpp=.o}
directory	:= out

.PHONY : flash build ${objects} ${output}.elf ${directory} format syntax clean

all : build flash


${objects} : %.o : %.cpp
	${compilier} ${flags} -c $^ -o ${directory}/$@

${output}.elf : ${objects}
	${compilier} ${flags} -o ${directory}/${output}.elf ${patsubst %.o,${directory}/%.o,${objects}}

flash : 
	${uploader} -c ${bootloader} -P ${port} -b ${baudrate} -p ${device} -D -U flash:w:${directory}/${output}.hex:i

build : ${directory} ${objects} ${output}.elf
	avr-objcopy -O ihex ${directory}/${output}.elf ${directory}/${output}.hex

syntax : ${sources}
	${compilier} ${flags} -fsyntax-only $^ 

format : ${sources}
	for file in ${sources}; do	\
		clang-format -i $$file; \
	done

${directory} :
	mkdir -p ${directory}

clean :
	rm -rf ${directory}

