#include "vga.h"
#include "kb.h"
#include "zz.h"
#include "kernel_assert.h"
#include "multiboot.h"
#include "idt.h"

void kmain(unsigned long magic, unsigned long addr) {
	int i;
	multiboot_info_t *mbi;
	mbi = (multiboot_info_t *) addr;
	kb_buf='\0';	
	doidt(0x21, IRQ1);

	locate(0, 0);
	setattr(0x00); 
	cls();
	locate(1, 0);
	setattr(0x14);
	write('*');
	
	setattr(0x1f);
	locate(0, 2);
	write(' ');
	locate(1, 2);
	write(' ');
	locate(1, 3);
	write(' ');
	locate(1, 4);
	write(' ');
	locate(1, 5);
	write(' ');
	locate(0, 6);
	kprint("   ");

	locate(3, 6);
	write(' ');
	locate(4, 5);
	write(' ');
	locate(5, 4);
	write(' ');
	locate(6, 3);
	write(' ');
	locate(7, 2);
	write(' ');
	locate(8, 1);
	write(' ');
	locate(9, 0);
	write(' ');

	locate(9, 6);
	write(' ');
	locate(8, 5);
	write(' ');
	locate(7, 4);
	write(' ');
	locate(5, 2);
	write(' ');
	locate(4, 1);
	write(' ');
	locate(3, 0);
	write(' ');
	
	locate(10, 6);
	kprint("        ");

	locate(0, 7);
	setattr(0x02);
	kprint("(c) 2010 John Ohno");

	setattr(0x07);
	locate(5, 9);
	kprint("PRESS ANY KEY TO CONTINUE");
	while(kb_buf=='\0') { 
		setattr(0x70);
		locate(5, 9);
		kprint("PRESS ANY KEY TO CONTINUE");
		for (i=0; i<100000; i++) { }
		setattr(0x07);
		locate(5, 9);
		kprint("PRESS ANY KEY TO CONTINUE");
		for (i=0; i<100000; i++) { }
	}
	kernel_assert(0, "ix_main.c", "84");
	cls();
	while(1) {
		asm("hlt");
	}
}

