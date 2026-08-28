#include "vga.h"
#include "io.h"

unsigned short	screens[4][80 * 25];
int				current_screen = 0;
int				screens_x[4];
int				screens_y[4];

unsigned short	*vga = (unsigned short *)0xB8000;
int				cursor_x;
int				cursor_y;
unsigned char	current_color;

void vga_putchar(char c, unsigned char color)
{
	if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
		if (cursor_y == 25)
		{
			vga_scroll();
		}
		vga_update_cursor(cursor_x, cursor_y);
		return ;
	}

	unsigned short entry = (color << 8) | c;
	vga[cursor_y * 80 + cursor_x] = entry;
	
	cursor_x++;
	if(cursor_x == 80)
	{
		cursor_y++;
		cursor_x = 0;
	}
	if (cursor_y == 25)
	{
		vga_scroll();
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

void	vga_scroll(void)
{
	int n = 24 * 80 * 2;

	memcpy(vga, vga + 80, n);
	int i = 0;
	while (i < 80)
	{
		vga[24 * 80 + i] = (vga_color(VGA_BRIGHT_WHITE, VGA_BLACK) << 8) | ' ';
		i++;
	}
	cursor_y = 24;
}

void	vga_init(vga_color_t foreground, vga_color_t background)
{
	current_color = vga_color(foreground, background);
	cursor_x = 0;
	cursor_y = 0;

	int s = 0;
    while (s < 4)
    {
        int i = 0;
        while (i < 80 * 25)
        {
            screens[s][i] = (current_color << 8) | ' ';
            i++;
        }
        s++;
    }

	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 14);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void	switch_screen(int n)
{
	memcpy(screens[current_screen], vga, 80 * 25 *2);
	screens_x[current_screen] = cursor_x;
	screens_y[current_screen] = cursor_y;
	current_screen = n;
	cursor_x = screens_x[current_screen];
	cursor_y = screens_y[current_screen];
	memcpy(vga, screens[current_screen], 80 * 25 *2);
	vga_update_cursor(cursor_x, cursor_y);
}