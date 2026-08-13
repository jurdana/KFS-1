#include "vga.h"

/* kernel entry point, called by _start in boot.asm
	void return type: the kernel never returns
	if it does, boot.asm catches it with the infinite hang loop */
void	kmain(void)
{
	/* writes "42" on screen at column 0, row 0
		15 = white foreground on black background (VGA color code) */
	vga_putstr("42", 15, 0, 0);
}