#include "vga.h"

/* pointer to the VGA text mode buffer
	0xB8000 is the fixed memory address of the VGA buffer
	unsigned short = 2 bytes per entry (1 byte character + 1 byte color) */
unsigned short *vga = (unsigned short *)0xB8000;

/* writes a single character at position (x, y) on screen with a given color
	c		: ASCII character to display
	color	: color byte (4 bits background | 4 bits foreground)
	x		: column (0 to 79)
	y		: row (0 to 24) */
void vga_putchar(char c, unsigned char color, int x, int y)
{
	/* encodes character and color into a single 16-bit value
		color is shifted 8 bits left to occupy the high byte
		c occupies the low byte
		result: [color (8 bits)][character (8bits)] */
	unsigned short entry = (color << 8) | c;

	/* writes the entry at the correct position in the buffer
		y * 80 : moves to the correct row (80 characters per row)
		+ x    : moves to the correct column */
	vga[y * 80 + x] = entry;
}

/* writes a null-terminated string starting at the position (x, y) with a given color
	str		: string to display
	color	: color byte (4 bits background | 4 bits foreground)
	x		: column (0 to 79)
	y		: row (0 to 24) */
void vga_putstr(char *str, unsigned char color, int x, int y)
{
	int i = 0;

	while (str[i])
	{
		/* writes the current character at the current position */
		vga_putchar(str[i], color, x, y);
		i++; /* next chracter*/
		x++; /* moves to the next column on screen */

		/* handles line wrapping when the end of a raw is reached */
		if(x == 80)
		{
			y++;	/* moves to the next row */
			x = 0;	/* resets column to the beginning of the row */
		}
	}
}