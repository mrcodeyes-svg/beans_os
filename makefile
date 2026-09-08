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
boot.bin: src\boot.asm folder
	$(NASM) -f bin src\boot.asm -o build\boot.bin

# Assemble entry stub
kernel_entry.o: src\enter_ker.asm folder
	$(NASM) -f win32 src\enter_ker.asm -o build\kernel_entry.o

# Compile C kernel
kernel.o: src\kernel.c folder
	$(CC) $(CFLAGS) -c src\kernel.c -o build\kernel.o

#compile stuff for the keyboard
keyboard.o: src\keyboard\keyboard.c folder
	$(CC) $(CFLAGS) -c src\keyboard\keyboard.c -o build\keyboard.o

#compile the stuff for the screen
screen.o: src\screen\screen.c folder
	$(CC) $(CFLAGS) -c src\screen\screen.c -o build\screen.o

# Link object files into an ELF/PE intermediate file using linker script
kernel.tmp: kernel_entry.o kernel.o keyboard.o screen.o folder
	$(CC) $(CFLAGS) -T src\linker.ld build\keyboard.o build\screen.o build\kernel_entry.o build\kernel.o -o build\kernel.tmp

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