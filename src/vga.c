#ifndef vga_c
#define vga_c
#include "vga.h"
unsigned char* video;
void locate(int x, int y) { //@ 
	cursorx=x;
	cursory=y;
}

void write(char c) { //@ 
/*	((vgapair*)screen[cursorx][cursory])->c=c;
	((vgapair*)screen[cursorx][cursory])->attr=color;
	cursorx++;
	if(cursorx > VGAX) {
		cursorx=0;
		cursory++;
	}
	while(cursory > VGAY) {
		scroll(1);
	}
*/
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
/*	int i, j, k;
	for(i=0; i<numlines; i++) {
		for(j=1; j<VGAY; j++) {
			for(k=0; k<VGAX; k++) {
				((vgapair*)screen[k][j-1])->c=((vgapair*)screen[k][j])->c;
				((vgapair*)screen[k][j-1])->attr=((vgapair*)screen[k][j])->attr;
				((vgapair*)screen[k][j])->c=' ';
				((vgapair*)screen[k][j])->attr=color;
			}
		}
	}*/

}

void setattr(char attr) { //@ attr is in vga color mode format
	color = attr;
}

void kprint(char* c) { //@ 
	int i=0;
	while(c[i]>0) {
		write(c[i]);
		i++;
	}
}

void cls() { //@ 
	int i;

	video = (unsigned char *) VGAADDR;
	    
	for (i = 0; i < VGAX * VGAY * 2; i++)
	*(video + i) = 0;

	cursorx = 0;
	cursory = 0;

}

#endif
