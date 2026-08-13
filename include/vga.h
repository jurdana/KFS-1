#ifndef VGA_H
#define VGA_H

void vga_putchar(char c, unsigned char color, int x, int y);
void vga_putstr(char *str, unsigned char color, int x, int y);

#endif