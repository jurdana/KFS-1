#ifndef VGA_H
#define VGA_H

extern unsigned char current_color;

typedef enum {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_WHITE = 7,
	VGA_GRAY = 8,
	VGA_LIGHT_BLUE = 9,
	VGA_LIGHT_GREEN = 10,
	VGA_LIGHT_CYAN = 11,
	VGA_LIGHT_RED = 12,
	VGA_LIGHT_MAGENTA = 13,
	VGA_YELLOW = 14,
	VGA_BRIGHT_WHITE = 15,
} vga_color_t;

void			vga_putchar(char c, unsigned char color);
void			vga_putstr(char *str, unsigned char color);

unsigned char	vga_color(vga_color_t foregroung, vga_color_t background);

void	vga_update_cursor(int x, int y);

void	vga_init(vga_color_t foreground, vga_color_t background);

void	switch_screen(int n);

#endif