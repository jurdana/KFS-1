#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"
#include "printk.h"

void	kmain(void)
{
		
// {
//	int i = 0;
// 	while (i < 46)
// 	{
// 		vga_putstr("4222222222222 7777\n", vga_color(VGA_BLACK, VGA_BRIGHT_WHITE));
// 		i++;
// 	}
// }


// {
	// vga_init(VGA_BRIGHT_WHITE, VGA_BLACK);
	// printk("Hello %s ! %d + %d = %d\n", "kernel", 21, 21, 42);
// }

	vga_init(VGA_BRIGHT_WHITE, VGA_BLACK);

	idt_init();
	pic_init();
	
	idt_set_gate(33, (unsigned int)keyboard_stub, 0x10, 0x8E);
	while (1)
		__asm__ volatile ("sti");
}