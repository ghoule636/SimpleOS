# Automatically generate list of sources with wildcards
C_SOURCES = $(wildcard kernel/*.c) # TODO add c driver files to sources!
HEADERS = $(wildcard kernel/*.h)

# TODO Make sources dep on all header files

# Convert the *.c filenames to *.o
OBJ = ${C_SOURCES:.c=.o}

CC = ~/opt/cross/bin/i386-elf-gcc

all: os-image.bin

run: all
	qemu-system-i386 -fda os-image.bin

os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	${CC} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean: 
	rm -rf *.bin *.dis *.o os-image.bin
	rm -rf kernel/*.o boot/*.bin
