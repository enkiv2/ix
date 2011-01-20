#include "idt.h"
#include "io.h"
struct IDTDescr my_idt[0x7ff];

void doidt(int irq, void (*handler)(void)) {
	asm("cli");
	asm("sidt my_idt");
	my_idt[irq].offset_1[0]=(unsigned char)((unsigned int)*handler);
	my_idt[irq].offset_1[1]=(unsigned char)(((unsigned int)*handler)>>8);
	my_idt[irq].offset_2[0]=(unsigned char)(((unsigned int)*handler)>>16);
	my_idt[irq].offset_2[1]=(unsigned char)(((unsigned int)*handler)>>24);
	asm("lidt my_idt");
	asm("sti");
	if(irq>=0x20 && irq<0x20+19) {
		if(irq<0x27) {
			char c=inportb(0xa1);
			outportb(0xa1, c & (~(1<<irq)));
		} else {
			char c=inportb(0x21);
			outportb(0x21, c & (~(1<<irq)));
		}
	}
}

