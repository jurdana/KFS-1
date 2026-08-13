ENTRY(_start)		/* declares _start as the binary entry point
						the linker uses this to know where execution begins */

SECTIONS { 			/* defines how sections from all object files are arranged in memory */

	. = 0x100000;	/* sets the location counter to 1 MB (0x100000)
					 everything below is reserved by the BIOS
					 GRUB expects to load the kernel at this address */

	.text : {			/* executable code section */
		*(.multiboot)	/* places the Multiboot header first, from all object files
							must be within the first 8 KB so GRUB can find it */
		*(.text)		/* places all executable code after the Multiboot header
							'*' means "from all object files" */
	}

	.data : {			/* initialized global variables section */
		*(.data)		/* collects .data sections from all object files */
	}

	.bss : {			/* uninitialized global variables section */
		*(.bss)			/* collects .bss sections from all object files
							includes the stack defined in boot.asm */
	}
}