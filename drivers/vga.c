#include "vga.h"

unsigned short *vga = (unsigned short *)0xB8000;


void vga_putchar(char c, unsigned char color, int x, int y)
{
	unsigned short entry = (color << 8) | c;
	vga[y * 80 + x] = entry;
}

void vga_putstr(char *str, unsigned char color, int x, int y)
{
	int i = 0;

	while (str[i])
	{
		vga_putchar(str[i], color, x, y);
		i++;
		x++;
		if(x == 80)
		{
			y++;
			x = 0;
		}
	}

}