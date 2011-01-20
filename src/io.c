#include "io.h"

unsigned char inportb(unsigned int port) {
	// read a byte from a port
	unsigned char ret;
	asm volatile ("inb %%dx,%%al":"=a"(ret):"d"(port));
	return ret;
}
void outportb(unsigned int port,unsigned char value) {
	// write a byte to a port
	asm volatile ("outb %%al,%%dx": :"d"(port),"a"(value));
}

