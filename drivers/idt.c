#include "idt.h"

idt_entry_t	idt[256];
idt_ptr_t	idt_ptr;

void	idt_set_gate(int n, unsigned int handler,
		unsigned short selector, unsigned char flags)
{
	idt[n].offset_low = handler & 0xFFFF;
	idt[n].selector = selector; // 0x08
	idt[n].zero = 0;
	idt[n].flags = flags; // 0x8E
	idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void	idt_init(void)
{
	idt_ptr.limit = sizeof(idt) - 1;
	idt_ptr.base = (unsigned int)idt;

	__asm__ volatile ("lidt (%0)" : : "r"(&idt_ptr));
}