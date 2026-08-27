#include "keyboard.h"
#include "vga.h"
#include "io.h"

static char keymap[] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
	0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*', 0, ' '
};

void	keyboard_handler(void)
{
	unsigned char scancode = inb(0x60);

	if (scancode < sizeof(keymap))
	{
		char c = keymap[scancode];
		if (c != 0)
			vga_putchar(c, current_color);
	}
	outb(0x20, 0x20);
}