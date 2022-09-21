# Automatically generate list of sources with wildcards
C_SOURCES = $(wildcard kernel/*.c) # TODO add c driver files to sources!
HEADERS = $(wildcard kernel/*.h)

# Convert the *.c filenames to *.o
OBJ = ${C_SOURCES:.c=.o}

# specify the gcc cross compiler
CC = ~/opt/cross/bin/i386-elf-gcc

# default build everything
all: os-image.bin

# runs the OS using qemu
run: all
	qemu-system-i386 -fda os-image.bin

# the disk image the computer loads which is the bootsector and kernel combined
os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

# the binary of our kernel
kernel.bin: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rules for compiling C files
%.o: %.c ${HEADERS}
	${CC} -ffreestanding -c $< -o $@

# compile the kernel_entry.asm to .o
%.o: %.asm
	nasm $< -f elf -o $@

# generic rules for compiling .asm files
%.bin: %.asm
	nasm $< -f bin -o $@

clean: 
	rm -rf *.bin *.dis *.o os-image.bin
	rm -rf kernel/*.o boot/*.bin