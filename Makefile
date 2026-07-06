uploader	:= avrdude
device		:= atmega328p
bootloader	:= arduino
baudrate	:= 115200
clock		:= 1000000UL
port		:= /dev/tty.usbserial-140

compilier	:= avr-gcc
flags		:= -mmcu=${device} -pedantic -Wall -DF_CPU=${clock} -Os
out		:= firmware
src		:= ${wildcard *.cpp}
obj		:= ${src:.cpp=.o}
dir		:= out

.PHONY : flash build ${obj} ${out}.elf ${dir} format syntax clear

all : build flash


${obj} : %.o : %.cpp
	${compilier} ${flags} -c $^ -o ${dir}/$@

${out}.elf : ${obj}
	${compilier} ${flags} -o ${dir}/${out}.elf ${patsubst %.o,${dir}/%.o,${obj}}

flash : 
	${uploader} -c ${bootloader} -P ${port} -b ${baudrate} -p ${device}  -D -U flash:w:${dir}/${out}.hex:i

build : ${dir} ${obj} ${out}.elf
	avr-objcopy -O ihex ${dir}/${out}.elf ${dir}/${out}.hex

syntax : ${src}
	${compilier} ${flags} -fsyntax-only $^ 

format : ${src}
	for file in ${src}; do		\
		clang-format -i $$file; \
	done

${dir} :
	mkdir -p ${dir}

clean :
	rm -rf ${dir}

