#include "vga.h"
#include "kb.h"
#include "zz.h"
#include "kernel_assert.h"
#include "multiboot.h"
#include "idt.h"
#include "system.h"

#define WAIT 100000000

void kmain(unsigned long magic, unsigned long addr) {
	int i;
	multiboot_info_t *mbi;
	mbi = (multiboot_info_t *) addr;
	kb_buf='\0';	
	
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	keyboard_install();
	timer_install();
	
	asm("sti");

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
	puts("   ");

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
	puts("        ");

	locate(0, 7);
	setattr(0x02);
	puts("(c) 2010 John Ohno");

	setattr(0x07);
	locate(5, 9);
	puts("PRESS ANY KEY TO CONTINUE");
	while(kb_buf=='\0') { 
		setattr(0x70);
		locate(5, 9);
		puts("PRESS ANY KEY TO CONTINUE");
		for (i=0; i<WAIT; i++) { }
		setattr(0x07);
		locate(5, 9);
		puts("PRESS ANY KEY TO CONTINUE");
		for (i=0; i<WAIT; i++) { }
	}
	
	init_cells();	

	kb_buf=0;	
	shadowbox(5, 5, 20, 10, "Welcome to ix. Use\n   w\na      d\n   s   to navigate, and i to edit", 0x20, 0x02);
	while (!kb_buf);

	cls();
	renice(spawn(nav_cells), 6);
	request_atomicity(0); // begin multithreading
	
}

