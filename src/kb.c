#ifndef kb_c
#define kb_c
#include "kb.h"

void handle_kb() { //@ keyboard handler converts scancode and puts ascii onto kb_buf
		   //@ kb_cmd is set to the scancode for a nonprintable character
		   //@ private variable mode is set to 1 for shift, 2 for control
		   //@ private variable caps is set for capslock
	kernel_assert(0, "kb.c" "6");
	char scan;
	scan=inportb(kb_port);
	if(scan==0x2a || scan==0x36) {
		mode=1;
	} else if(scan>0x39 && scan<0x57) {
		if(scan==0x3a) {
			if(caps) {
				caps=0;
			} else {
				caps=1;
				mode=1;
			}
		}
		kb_cmd=scan;
	} else {
		kb_buf=kb_map[scan][mode];
		if(!caps) { mode=0; }
	}
	outportb(0x20, 0x20); // tell the kb controller that the handler is done
	asm("iret");
}

#endif
