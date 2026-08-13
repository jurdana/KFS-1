extern kmain

global _start

section .multiboot
    dd 0x1BADB002           ; magic number / dd = Define Double word
    dd 0x0                  ; flags
    dd -(0x1BADB002 + 0x0)  ; checksum

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