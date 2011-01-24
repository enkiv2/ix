#ifndef zz_c
#define zz_c
#include "zz.h"

void display_cells() { //@ displays based on currcell, in xbar form
	int i;
	zzcell* curr;
	zzcell* yneg;
	zzcell* ypos;
	zzcell* xneg;
	zzcell* xpos;
	int offset;

	curr=get_cell(currcell);
	offset=curr->end - curr->start;
	if(offset > 10 /* max offset is small */ ) {
		offset = 10;
	}
	scroll(VGAY); /* clear the screen */
	locate(VGAX/2 - offset/2, VGAY/2);

	yneg=get_cell(curr->connections[dimy][0]);
	offset=yneg->end - yneg->start;
	if(offset > 10) {
		offset=10;
	}
	locate(VGAX/2 - offset/2, 0);
	write_cell(yneg, offset);

	ypos=get_cell(curr->connections[dimy][1]);
	offset=ypos->end - ypos->start;
	if(offset > 10) {
		offset=10;
	}
	locate(VGAX/2 - offset/2, VGAY-2);
	write_cell(ypos, offset);

	xneg=get_cell(curr->connections[dimx][0]);
	locate(0, VGAY/2);
	write_cell(xneg, VGAX/2 - 5);

	xpos=get_cell(curr->connections[dimx][1]);
	offset=xpos->end - xpos->start;
	if(offset > VGAX/2 - 5) {
		offset=VGAX/2 - 5;
	}
	locate(VGAX-offset, VGAY/2);
	write_cell(xpos, offset);
}

zzcell* get_cell(int id) { //@
	return (zzcell*) (cells_begin + (id * sizeof(zzcell)));
}

void write_cell(zzcell* cell, int limit) { //@ displays a given cell. limit is
					   //@ the cutoff, and -1 for full file
	int i;
	if(limit < 0) {
		limit = cell->end + limit;
	}
	for(i=0; i<limit; i++) {
		write(*((char*)((istream_begin) + cell->start + i)));
	}
}
#endif

