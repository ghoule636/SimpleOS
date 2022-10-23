# Automatically generate list of sources with wildcards
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

# Convert the *.c filenames to *.o
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

# specify the gcc cross compiler
CC = ~/opt/cross/bin/i386-elf-gcc
GDB = ~/opt/cross/bin/i386-elfgdb

CFLAGS = -g -Wextra -Wall -ffreestanding
LDFLAGS = -T link.ld

# default build everything
all: os-image.bin

# runs the OS using qemu
run: all
	qemu-system-i386 -fda os-image.bin

# debug configuration using GDB
debug: os-image.bin kernel.elf
	qemu-system-i386 -fda os-image.bin -s -S &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# the disk image the computer loads which is the bootsector and kernel combined
os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

# the binary of our kernel
kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld $(LDFLAGS) -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld $(LDFLAGS) -o $@ -Ttext 0x1000 $^

# Generic rules for compiling C files
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

# compile the kernel_entry.asm to .o
%.o: %.asm
	nasm $< -f elf -o $@

# generic rules for compiling .asm files
%.bin: %.asm
	nasm $< -f bin -o $@

clean: 
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin boot/*.o drivers/*.o cpu/*.o libc/*.o
