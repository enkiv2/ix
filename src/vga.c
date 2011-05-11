#ifndef vga_c
#define vga_c
#include "vga.h"
#include "system.h"
#include "kb.h"

unsigned char* video;

const char* editpane(int x, int y, int width, int height, char* text, int maxlen, int fg, int bg) {
	if(kb_buf) {
		if(kb_buf==27) return text; // ESC
		if(kb_buf=='\b') {
			text[strlen(text)-1]=0;
		} else if(strlen(text)<maxlen-1) {
			text[strlen(text)+1]='\0';
			text[strlen(text)]=kb_buf;
			kb_buf=0;
		} else puts("\a"); // bell
	}
	shadowbox(x, y, width, height, text, fg, bg);
}

void shadowbox(int x, int y, int width, int height, char* text, int fg, int bg) {
	int i, j, k, col, linegoing;
	col=color;
	k=0;
	linegoing=0;
	for(i=x; i<x+width+1; i++) {
		for(j=y; j<y+height+1; j++) {
			locate(i, j);
			if(i==x+width || j==y+height) {
				setattr(bg);
				puts(" ");
			} else {
				setattr(fg);
				if(k<strlen(text)&&!linegoing) {
					if(text[k]=='\n' || text[k]=='\r') {
						linegoing=1;
					} else	putch(text[k]);
				} else puts(" ");
				k++;
			}
		}
		linegoing=0;
	}
}

void locate(int x, int y) { //@ 
	cursorx=x;
	cursory=y;
}

void putch(char c) { //@ alias for write
	write(c);
}

void write(char c) { //@ 
	if (c == '\n' || c == '\r') {
		newline:
		cursorx = 0;
	      	cursory++;
	}
	if (cursory >= VGAY) {
		cursory = 0;
		return;
	}
	*(video + (cursorx + cursory * VGAX) * 2) = c & 0xFF;
	*(video + (cursorx + cursory * VGAX) * 2 + 1) = color;
		
	cursorx++;
	if (cursorx > VGAX)
		goto newline;

}

void scroll(int numlines) { //@ not implemented
	int i, j;
	for(i=numlines; i<VGAY; i++) {
		for(j=0; j<VGAX*2; j++) {
			*(video + (j + (i-numlines) * VGAX * 2))=*(video + (j + i * VGAX * 2));
		}
	}
}

void setattr(char attr) { //@ attr is in vga color mode format
	color = attr;
}


void puts(char* c) { //@ 
	int i=0;
	while(c[i]>0) {
		write(c[i]);
		i++;
	}
}

void cls() { //@
	displaytime();
	int i;

	video = (unsigned char *) VGAADDR;
	    
	for (i = 0; i < VGAX * VGAY * 2; i++)
	*(video + i) = 0;

	cursorx = 0;
	cursory = 0;

}

#endif
