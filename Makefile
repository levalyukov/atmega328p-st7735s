uploader	:= avrdude
device		:= atmega328p
bootloader	:= arduino
baudrate	:= 115200
port		:= /dev/tty.usbserial-140
clock		:= 1000000UL

compilier	:= avr-gcc
flags		:= -mmcu=${device} -pedantic -Wall -D F_CPU=${clock} -Os
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
	for file in ${sources}; do		\
		clang-format -i $$file; \
	done

${directory} :
	mkdir -p ${directory}

clean :
	rm -rf ${directory}

