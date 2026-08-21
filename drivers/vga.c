#include "vga.h"
#include "io.h"

unsigned short	*vga = (unsigned short *)0xB8000;
int				cursor_x = 0;
int				cursor_y = 0;

void vga_putchar(char c, unsigned char color)
{
	unsigned short entry = (color << 8) | c;
	vga[cursor_y * 80 + cursor_x] = entry;
	
	cursor_x++;
	if(cursor_x == 80)
	{
		cursor_y++;
		cursor_x = 0;
	}
	vga_update_cursor(cursor_x, cursor_y);
}

void vga_putstr(char *str, unsigned char color)
{
	int i = 0;

	while (str[i])
	{
		vga_putchar(str[i], color);
		i++;
	}
}

unsigned char	vga_color(vga_color_t foreground, vga_color_t background)
{
	return ((background << 4) | foreground);
}

void	vga_update_cursor(int x, int y)
{
	int	position = y * 80 + x;

	outb(0x3D4, 0x0E);
	outb(0x3D5, position >> 8);

	outb(0x3D4, 0x0F);
	outb(0x3D5, position & 0xFF);
}