#include <system.h>
#define kb_c
#include "kb.h"


/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r) {
	request_atomicity(1);
	unsigned char scancode;
	
	/* Read from the keyboard's data buffer */
	scancode = inportb(0x60);
	kb_cmd=scancode;
	
	if (!(scancode & 0x80)) {
		//scancode &= 0x7f; // clear the top bit
		if (scancode==42 || scancode==54) { // shifts
			mode|=1;
		} else if(scancode==58) { // capslock
			if(mode&3) {
				mode^=3;
			} else {
				mode|=3;
			}
		} else if(mode&1) {
			kb_buf=kbdus_qwerty_shifted[scancode];
			/*if(!(mode&3)) */ mode&=0xfe; // turn off caps
		} else {
			kb_buf=kbdus_qwerty[scancode];
		}
	}
	request_atomicity(0);
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_install() {
	irq_install_handler(1, keyboard_handler);
}

