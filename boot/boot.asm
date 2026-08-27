extern kmain
extern keyboard_handler

global _start
global keyboard_stub

section .multiboot
    dd 0x1BADB002
    dd 0x0
    dd -(0x1BADB002 + 0x0)

section .bss
    stack_bottom:
        resb 16384
    stack_top:

section .text
_start:
    mov esp, stack_top
    call kmain
.hang:
    cli
    hlt
    jmp .hang

keyboard_stub:
    pusha
    call keyboard_handler
    popa
    iret