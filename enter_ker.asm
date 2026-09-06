[bits 32]
[extern _kernel_main] ;we are using gcc for this so add a underscore

global _start
_start:
    call _kernel_main ;jump to kernel_main
    jmp $ ;hang