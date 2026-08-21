#include "vga.h"

void	kmain(void)
{
	int i = 0;

	while (i < 46)
	{
		vga_putstr("4222222222222 7777\n", vga_color(VGA_BLACK, VGA_BRIGHT_WHITE));
		i++;
	}

}