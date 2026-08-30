[org 0x7C00]
[bits 16] ;the bits

;the start
start:
    ;step 1 clear it all and set stuff up
    cli ;keep the cpu to our selfs
    xor ax, ax ;clear the ax reg and then clear out the rest too
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00 ;it gives calling and reting somewhere to go
    sti ;let others get the cpu

    ;step 2
    mov ah, 0x02 ;reads the sectors from the drive
    mov al, 8 ;the number of sectors the kernel takes up
    mov ch, 0 ;the cylinder number this is the first one
    mov cl, 2 ;the sector number set to 2 because the kernel starts at sector 2
    mov dh, 0 ;the first drive head
    ;dl is the drive number the bios does stuff with it
    mov bx, 0x1000 ;the buffer offset the bios writes the kernel sectors 0x0000:0x1000
    int 0x13 ;read from the disk

    ;step 3
    mov ah, 0x0E ;the char output
    mov al, 'h' ;the thing we output
    int 0x10 ;call bios

    ;load the a20 lines 
    in al, 0x92
    or al, 2
    out 0x92, al

    ;step 4
    cli
    lgdt [gdt_descriptor] ;load the gdp
    mov eax, cr0 ;moves the contents of control register 0 to eax
    or eax, 0x1 ;turn on protected mode
    mov cr0, eax ;moves the stuff from eax to cr0

    jmp CODE_SEG:init_pm ;jump

[bits 32] ;load into the 32 bit zone
;step 1
init_pm:
    mov ax, DATA_SEG ;update the seg regs to 32 bit
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x90000 ;move the stack down out of the way
    mov esp, ebp ;move the stuff in ebp into esp

    jmp 0x1000 ;jump to the c code

;step 2
;gdt table
gdt_start:

gdt_null:
    dd 0x0 ;make this null
    dd 0x0 ;do it again

gdt_code:
    dw 0xFFFF ;a limit from 0 to 15 bit
    dw 0x0000 ;the base 0 to 16 bit
    db 0x00 ;another base just 16 to 23 bit this time
    db 10011010b ;idk gng
    db 11001111b ;still dont know
    db 0x00 ;i know this one base 24 to 31 bit

gdt_data: ;samething as last time now just bigger and mostly db              
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end: ;the end

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ;the size - 1
    dd gdt_start ;where we start

CODE_SEG equ gdt_code - gdt_start   ; 0x08
DATA_SEG equ gdt_data - gdt_start   ; 0x10

;pad
times 510-($-$$) db 0 ;yeah this just does 0s
dw 0xAA55 ;bootloader signature