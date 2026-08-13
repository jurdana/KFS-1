extern kmain		; declares kmain as an external symbol (defined in kmain.c)

global _start		; makes _start visible to the linker as the entry point

section .multiboot	; special section placed first in the binary by the linker script
					; GRUB looks for the magic number in the first 8 KB of the binary

    dd 0x1BADB002			; magic number: identifies the binary as a valid Multiboot kernel
							; dd = Define Double word, writes a 32-bit value into the binary
    dd 0x0					; flags: Multiboot options, 0x0 = no special options
    dd -(0x1BADB002 + 0x0)	; checksum: must satisfy magic + flags +checksum = 0
							; GRUB verifies this sum to confirm the header is valid

section .bss		; section for uninitialized variables, takes no space in the binary
    stack_bottom:	; label marking the start of the reserved memory zone for the stack
        resb 16384	; resb = Reserved Bytes
    stack_top:		; label marking the end of the zone - esp must point here
					; the stack grows downward so esp is initialized at the top

section .text		; section containing executable code

_start:					; kernel entry point, GRUB jumps here after loading the binary
    mov esp, stack_top	; initializes the stack pointer to the top of the stack
    call kmain			; without this, C cannot work (no function calls, no local variables)

.hang:			; local label (starts with .) - belongs to _start
    cli			; disables CPU interrupts (Clear Interrupt flag)
    hlt			; halts the CPU until the next interrupt (halt)
    jmp .hang	; if an interrupt wakes the CPU despite cli, loop back
				; the kernel must never exit this loop