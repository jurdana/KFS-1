#include "vga.h"
#include "printk.h"

void	kmain(void)
{
	int i = 0;

	vga_init(VGA_BRIGHT_WHITE, VGA_BLACK);


	printk("Hello %s ! %d + %d = %d\n", "kernel", 21, 21, 42);

	// while (i < 46)
	// {
	// 	vga_putstr("4222222222222 7777\n", vga_color(VGA_BLACK, VGA_BRIGHT_WHITE));
	// 	i++;
	// }

}