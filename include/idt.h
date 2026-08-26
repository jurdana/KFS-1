#ifndef IDT_H
#define IDT_H

typedef struct {
	unsigned short	offset_low;
	unsigned short	selector;
	unsigned char	zero;
	unsigned char	flags;
	unsigned short	offset_high;
}	__attribute__((packed)) idt_entry_t;

typedef struct {
	unsigned short	limit;
	unsigned int	base;
}	__attribute__((packed)) idt_ptr_t;

void	idt_set_gate(int n, unsigned int handler,
		unsigned short selector, unsigned char flags);
void	idt_init(void);

#endif