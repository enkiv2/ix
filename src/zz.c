#ifndef zz_c
#define zz_c
#include "zz.h"
#include "kb.h"

int zz_menu_choice;

void display_cells() { //@ displays based on currcell, in xbar form
	int i;
	zzcell* curr;
	zzcell* yneg;
	zzcell* ypos;
	zzcell* xneg;
	zzcell* xpos;
	int offset;
	
	setattr(0x07);
	
	curr=get_cell(currcell);

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
	offset=xneg->end - xneg->start;
	if(offset > 10) {
		offset=10;
	}
	locate(0, VGAY/2);
	write_cell(xneg, offset);

	xpos=get_cell(curr->connections[dimx][1]);
	offset=xpos->end - xpos->start;
	if(offset > 10) {
		offset=10;
	}
	locate(VGAX-offset, VGAY/2);
	write_cell(xpos, offset);

	offset=curr->end - curr->start;
	if(offset > 70) {
		offset=70;
	}
	locate((VGAX/2) - (offset/2), VGAY/2);
	setattr(0x20); // Current cell shouldn't just be bigger: it should pop
	write_cell(curr, offset);
}

zzcell* get_cell(int id) { //@
	return (zzcell*) (cells_begin + (id * sizeof(zzcell)));
}

void init_cells() { //@ Makes a clean zzspace with some default cells
	int i;

	currcell_old=0;
	currcell=0;
	maxcell=2;

	zz_mode=zz_display_mode;
	zzcell* cell;
	const char welcomestr[14]="Welcome to Ix";
	const char helpstr[34]="Help: wasd to navigate, i to edit";
	for(i=0; i<max_cells; i++) {
		cell=get_cell(i);
		cell->start=0;
		cell->end=0;
		int j;
		for(j=0; j<max_dims; j++) {
			cell->connections[j][0]=0;
			cell->connections[j][1]=0;
		}
	}
	currcell=0;
	cell=get_cell(0);
	cell->start=0;
	cell->end=14;
	for(i=0; i<14; i++) {
		*((char*)((istream_begin)+cell->start + i))=welcomestr[i];
	}
	cell->connections[0][0]=1;
	cell=get_cell(1);
	cell->start=15;
	cell->end=49;
	for(i=0; i<34; i++) {
		*((char*)((istream_begin)+cell->start+i))=helpstr[i];
	}
	

	
}

void display_editmenu() {
	locate(0, 0);
	puts("Edit menu:\nUse wasd to navigate.");
	
	if(zz_menu_choice>=5 || zz_menu_choice < 0) {
		zz_menu_choice=0;
	}
	
	int i;
	for(i=0; i<5; i++) {
		locate(10, 5+i);
		if(i==zz_menu_choice) {
			setattr(0x20);
		} else setattr(0x07);
		switch(i) {
			case 0:
				puts("New cell");
				break;
			case 1:
				puts("Connect cell");
				break;
			case 2:
				puts("Edit cell contents");
				break;
			case 3:
				puts("Remove this cell");
				break;
			case 4:
				puts("Nevermind");
				break;
		}
	}
}

void nav_cells() { 	//@ handle navigation, display, and editing
			//@ TODO: editing support
	if(zz_mode == zz_display_mode) {
		if (kb_buf) cls();
		switch(kb_buf) {
			case 'i':
				zz_mode=zz_edit_mode;
				break;
			case 'w':
				currcell=get_cell(currcell)->connections[dimy][0];
				break;
			case 'a':
				currcell=get_cell(currcell)->connections[dimx][0];
				break;
			case 's':
				currcell=get_cell(currcell)->connections[dimy][1];
				break;
			case 'd':
				currcell=get_cell(currcell)->connections[dimx][1];
				break;
		}
		kb_buf='\0';
		if(zz_mode==zz_display_mode) display_cells(); // hack
	} else {
		if(zz_mode==zz_edit_mode) {
			if(kb_buf) cls();
			switch(kb_buf) {
				case 'w':
					zz_menu_choice--;
					cls();
					kb_buf='\0';
					display_editmenu();
					break;
				case 's':
					zz_menu_choice++;
					cls();
					kb_buf='\0';
					display_editmenu();
					break;
				case 'a':
					cls();
					kb_buf='\0';
					zz_mode=zz_display_mode;
					break;
				case 'd':
				case '\n':
					cls();
					kb_buf='\0';
					zz_mode=zz_selected_mode;
					break;
				default:
					display_editmenu();
					break;
			}
		}
	}

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

