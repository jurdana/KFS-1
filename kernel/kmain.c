#include "vga.h"

void	kmain(void)
{
	vga_putstr("42", vga_color(VGA_BLACK, VGA_BRIGHT_WHITE));
}