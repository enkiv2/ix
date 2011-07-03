#ifndef zz_c
#define zz_c
#include "zz.h"
#include "kb.h"
#include "system.h"

int zz_menu_choice;
const inline void relink();
inline void display_cells() { //@ displays based on currcell, in xbar form
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

	dimx=0;
	dimy=1;
	modality=0;

	currcell_old=0;
	currcell=0;
	maxcell=2;

	zz_mode=zz_display_mode;
	zzcell* cell;
	const char welcomestr[14]="Welcome to Ix";
	const char helpstr[34]="Help: wasd to navigate, i to edit";
	for(i=0; i<max_cells; i++) {
		cell=get_cell(i);
		cell->start=i*512;
		cell->end=((i+1)*512) - 1;
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
	//cell->start=15;
	cell->end=546;
	for(i=0; i<34; i++) {
		*((char*)((istream_begin)+cell->start+i))=helpstr[i];
	}
	

	
}

inline void display_editmenu() {
	
	int i;
	/* shadowbox */
	setattr(0x20);
	for(i=0;i<12; i++) {
		locate(0, i);
		puts("                        ");
	}

	setattr(0);
	for(i=1; i<11; i++) {
		locate(0, i);
		puts("                       ");
	}

	setattr(0x02);
	locate(1, 1);
	puts("Edit menu:");
	locate(0, 2);
	puts("Use wasd to navigate.");
	
	if(zz_menu_choice>=5 || zz_menu_choice < 0) {
		zz_menu_choice=0;
	}
	
	
	for(i=0; i<5; i++) {
		locate(5, 5+i);
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

const void nav_cells(int pid) { 	//@ handle navigation, display, and editing
			//@ TODO: editing support
	displaytime();
	int i;
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
			case 'f':
				fork();
				break;
			case 'x':
				dimx++;
				if(dimx>max_dims) dimx=0;
				break;
			case 'y':
				dimy++;
				if(dimy>max_dims) dimy=0;
				break;
			case 'm':
				locate(0, 0);
				puts("Marked!\n");
				get_cell(currcell_old)->connections[dimlink][forelink]=currcell;
				get_cell(currcell)->connections[dimlink][!forelink]=currcell_old;
				puts("Linked cell #");
				puts(itoa(currcell_old, editbuf));
				if(forelink) { puts("poswardly "); } else puts("negwardly ");
				puts("on dimension ");
				puts(itoa(dimlink, editbuf));
				puts(" to cell #");
				puts(itoa(currcell, editbuf));
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
		} else if(zz_mode==zz_selected_mode) {
			request_atomicity(1);
			if(modality==6) {
				if(!editpane(5, 5, VGAX-10, VGAY-10, editbuf, max_edit_size-2, 0x02, 0x20)) {
                                        yield();
                                } else {
                                        for(i=0; i<max_edit_size-2; i++) {
                                                if(editbuf[i]!=0) {
                                                        *((char*)((istream_begin)+get_cell(currcell)->start+i))=editbuf[i];
                                                } else {
                                                        *((char*)((istream_begin)+get_cell(currcell)->start+i))=editbuf[i];
                                                        get_cell(currcell)->end=get_cell(currcell)->start+i;
                                                        modality=0;
                                                        break;
                                                }
                                        }
					locate(0, 0);
        	                        puts("Marked!\n");
        	                        get_cell(currcell_old)->connections[dimlink][forelink]=currcell;
					get_cell(currcell)->connections[dimlink][!forelink]=currcell_old;
        	                        puts("Linked cell #");
                	                puts(itoa(currcell_old, editbuf));
                	                if(forelink) { puts("poswardly "); } else puts("negwardly ");
                	                puts("on dimension ");
                        	        puts(itoa(dimlink, editbuf));
                        	        puts(" to cell #");
                                	puts(itoa(currcell, editbuf));
				        modality=0;
					zz_mode=zz_display_mode;
                                }
			} else {
			if(zz_menu_choice==0 || modality==5) {
				if(!modality) {
			                cls();
                			display_cells();
                			locate(0, 0);
                			puts("Indicate direction of connection, or c to cancel");
               				modality=5;
     				} else {
			                if(kb_buf!='w' && kb_buf!='a' && kb_buf!='s' && kb_buf!='d' && kb_buf!='c') {
        			                timer_wait(1);
                			        displaytime();
                			        modality=5;
	  					yield();
			                } else {
                			        if(kb_buf=='c') {
      			                          zz_mode=zz_edit_mode;
			                        } else if(kb_buf=='w') {
			                                dimlink=dimy;
                			                forelink=0;
       				                } else if(kb_buf=='a') {
                			                dimlink=dimx;
          			                      forelink=0;
   				                } else if(kb_buf=='s') {
                    				            dimlink=dimy;

						} else if(kb_buf=='d') {
			                                dimlink=dimx;
                			                forelink=1;
                        			}
                      				locate(0, 1);
						currcell_old=currcell;
						currcell=maxcell;
						maxcell++;
						get_cell(currcell)->start=currcell*512;//get_cell(currcell-1)->end + 2;
						puts("Good! Now, compose your new cell.");
						modality=6;
						//for(i=0; i<512; i++) {
                                                //	editbuf[i]=0;//*((char*)((istream_begin) + get_cell(currcell)->start + i));
                                        	//}
                                        	for (i=i; i<max_edit_size-2; i++) {
                                                	//editbuf[(get_cell(currcell)->end - get_cell(currcell)->start)]=0;
                                                	editbuf[i]=0;
                                        	}
                                       		kb_buf=0;

					}
				}
			}
			if(zz_menu_choice==1 || modality==1) {
				relink();
			}
			if(zz_menu_choice==2 || modality==2) {
				int i;
				if(!modality) {
					modality=2;
					for(i=0; i<(get_cell(currcell)->end - get_cell(currcell)->start) && i<512; i++) {
						editbuf[i]=*((char*)((istream_begin) + get_cell(currcell)->start + i));
					}
					editbuf[i]=0;
					for (i=i; i<max_edit_size-2; i++) {
						editbuf[i]=0;
					}
					kb_buf=0;
				}
				if(!editpane(5, 5, VGAX-10, VGAY-10, editbuf, max_edit_size-2, 0x02, 0x20)) {
					yield();
				} else {
					for(i=0; i<max_edit_size-2 && editbuf[i]!=0; i++) 
						*((char*)((istream_begin)+get_cell(currcell)->start+i))=editbuf[i];
					*((char*)((istream_begin)+get_cell(currcell)->start+i))=editbuf[i];
					get_cell(currcell)->end=get_cell(currcell)->start+i;
					modality=0;		
				}
			}
			}
			if(!modality) {
				zz_mode=zz_display_mode;
				request_atomicity(0);
			}
		}
	}
}

const inline void relink() {
	if(!modality) {
		cls();
		display_cells();
		locate(0, 0);
		puts("Indicate direction of connection, or c to cancel");
		modality=1;
	} else {
		if(kb_buf!='w' && kb_buf!='a' && kb_buf!='s' && kb_buf!='d' && kb_buf!='c') {
			timer_wait(1);
			displaytime();
			modality=2;
			yield();
		} else {
			if(kb_buf=='c') {
				zz_mode=zz_edit_mode;
			} else if(kb_buf=='w') {
				dimlink=dimy;
				forelink=0;
			} else if(kb_buf=='a') {
				dimlink=dimx;
				forelink=0;
			} else if(kb_buf=='s') {
				dimlink=dimy;
				forelink=1;
			} else if(kb_buf=='d') {
				dimlink=dimx;
				forelink=1;
			}
			locate(0, 1);
			puts("Good! Now, navigate to the cell you want to link to and press 'm' to mark it.");
			currcell_old = currcell;
			modality=0;
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

