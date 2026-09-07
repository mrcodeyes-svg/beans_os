# Tools
NASM    = nasm
CC      = gcc
OBJCOPY = objcopy
QEMU    = qemu-system-i386

# Flags
CFLAGS  = -m32 -ffreestanding -fno-pie -nostdlib -Iinclude

# Default target
all: folder os-image.bin 

folder:
	if not exist build mkdir build

# Assemble bootloader
boot.bin: boot.asm folder
	$(NASM) -f bin boot.asm -o build\boot.bin

# Assemble entry stub
kernel_entry.o: enter_ker.asm folder
	$(NASM) -f win32 enter_ker.asm -o build\kernel_entry.o

# Compile C kernel
kernel.o: kernel.c folder
	$(CC) $(CFLAGS) -c kernel.c -o build\kernel.o

#compile the stuff for the screen
screen.o: screen\screen.c folder
	$(CC) $(CFLAGS) -c screen\screen.c -o build\screen.o

# Link object files into an ELF/PE intermediate file using linker script
kernel.tmp: kernel_entry.o kernel.o screen.o folder
	$(CC) $(CFLAGS) -T linker.ld build\screen.o build\kernel_entry.o build\kernel.o -o build\kernel.tmp

# Strip executable headers into a pure, raw binary
kernel.bin: kernel.tmp folder
	$(OBJCOPY) -O binary build\kernel.tmp build\kernel.bin

# Combine bootloader and kernel into a single image
os-image.bin: boot.bin kernel.bin folder
	cmd /c "copy /b build\boot.bin + build\kernel.bin build\os-image.bin"

# Build and run in QEMU
run: os-image.bin folder
	$(QEMU) -drive format=raw,file=build\os-image.bin

# Clean up built files
clean:
	if exist build rmdir /s /q build