#include <system.h>
#define kb_c
#include "kb.h"

unsigned char kbdus_qwerty[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
	0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,					/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};
unsigned char kbdus_qwerty_shifted[128] = {
        0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
        '(', ')', '_', '+', '\b',       /* Backspace */
        '\t',                   /* Tab */
        'Q', 'W', 'E', 'R',     /* 19 */
        'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',           /* Enter key */
        0,                      /* 29   - Control */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',       /* 39 */
        '\"', '~', 0,
	'|', 'Z', 'X', 'C', 'V', 'B', 'N',                     /* 49 */
        'M', ',', '.', '?',   0,                                        /* Right shift */
        '*',
        0,      /* Alt */
        ' ',    /* Space bar */
        0,      /* Caps lock */
        0,      /* 59 - F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,      /* < ... F10 */
        0,      /* 69 - Num lock*/
        0,      /* Scroll Lock */
        0,      /* Home key */
        0,      /* Up Arrow */
        0,      /* Page Up */
        '-',
        0,      /* Left Arrow */
        0,                                                                                                       
        0,      /* Right Arrow */                                                                                
        '+',
        79,     /* 79 - End key*/
        0,      /* Down Arrow */
        0,      /* Page Down */
        0,      /* Insert Key */
        0,      /* Delete Key */
        0,   0,   0,
        0,      /* F11 Key */
        0,      /* F12 Key */
        0,      /* All other keys are undefined */
};
unsigned char* kbcmd_trans = "w00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00sw00a0d00s";

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

