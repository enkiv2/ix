#include "idt.h"
#include "io.h"
struct IDTDescr my_idt[0x7ff];
struct IDTPtr x;
void doidt(int irq, void (*handler)(void)) { //@ set handler for irq and reload idt
	asm("cli");
	asm("sidt my_idt");
	my_idt[irq].offset_1=(uint16_t)((unsigned int)*handler);
	my_idt[irq].offset_2=(uint16_t)(((unsigned int)*handler)>>16);
	my_idt[irq].zero=0;
	my_idt[irq].selector=0x08;
	my_idt[irq].type_attr=0xE;
	x.size=0x7ff;
	x.desc=my_idt;
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

