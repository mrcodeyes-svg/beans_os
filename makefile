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

# Compile and link C kernel without PE image base warnings
kernel.tmp: kernel.c folder
	$(CC) $(CFLAGS) -Wl,--image-base=0x1000 -Ttext 0x1000 -Wl,-e,_kernel_main kernel.c include\stdiok.c -o build\kernel.tmp

# Strip PE headers to raw machine binary
kernel.bin: kernel.tmp folder
	$(OBJCOPY) -O binary build\kernel.tmp build\kernel.bin

# Binary copy for Windows CMD/PowerShell (replaces 'cat')
os-image.bin: boot.bin kernel.bin folder
	cmd /c "copy /b build\boot.bin + build\kernel.bin build\os-image.bin"

# Build and run in QEMU
run: os-image.bin folder
	$(QEMU) -drive format=raw,file=build\os-image.bin

# Clean up built files
clean:
	if exist build rmdir /s /q build