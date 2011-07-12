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
	if (yneg != curr)
		write_cell(yneg, offset);

	ypos=get_cell(curr->connections[dimy][1]);
	offset=ypos->end - ypos->start;
	if(offset > 10) {
		offset=10;
	}
	locate(VGAX/2 - offset/2, VGAY-2);
	if (ypos != curr)
		write_cell(ypos, offset);

	xneg=get_cell(curr->connections[dimx][0]);
	offset=xneg->end - xneg->start;
	if(offset > 10) {
		offset=10;
	}
	locate(0, VGAY/2);
	if (xneg != curr)
		write_cell(xneg, offset);

	xpos=get_cell(curr->connections[dimx][1]);
	offset=xpos->end - xpos->start;
	if(offset > 10) {
		offset=10;
	}
	locate(VGAX-offset, VGAY/2);
	if (xpos != curr)
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
	const char welcomestr[5]="Home";
	for(i=0; i<max_cells; i++) {
		cell=get_cell(i);
		cell->start=i*max_edit_size;
		cell->end=cell->start; // zero length
		int j;
		for(j=0; j<max_dims; j++) {
			cell->connections[j][0]=0;
			cell->connections[j][1]=0;
		}
	}
	currcell=1;
	cell=get_cell(1);
	cell->end=516;
	for(i=0; i<5; i++) {
		*((char*)((istream_begin)+cell->start + i))=welcomestr[i];
	}
}

inline void display_editmenu() {	
	int i; // TODO: replace this with a proper shadowbox
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
				puts("Insert cell");
				break;
			case 1:
				puts("Connect cell");
				break;
			case 2:
				puts("Edit cell contents");
				break;
			case 3:
				puts("Remove neighbour");
				break;
			case 4:
				puts("Nevermind");
				break;
		}
	}
}

const void nav_cells(int pid) { 	//@ handle navigation, display, and editing
	displaytime();
	int i;
	if (zz_mode==zz_delay_mode && kb_buf)
		zz_mode=zz_display_mode;
	if(zz_mode == zz_display_mode) {
		if (kb_buf) cls();
		switch(kb_buf) {
			case 'i':
				zz_mode=zz_edit_mode;
				break;
			case 'w':
				if(get_cell(currcell)->connections[dimy][0])
					currcell=get_cell(currcell)->connections[dimy][0];
				break;
			case 'a':
				if(get_cell(currcell)->connections[dimx][0])
					currcell=get_cell(currcell)->connections[dimx][0];
				break;
			case 's':
				if(get_cell(currcell)->connections[dimy][1])
					currcell=get_cell(currcell)->connections[dimy][1];
				break;
			case 'd':
				if(get_cell(currcell)->connections[dimx][1])
					currcell=get_cell(currcell)->connections[dimx][1];
				break;
			case 'f':
				fork();
				break;
			case 'X':
				dimx--;
				if(dimx<0) dimx=max_dims;
				break;
			case 'Y':
				dimy--;
				if(dimy<0) dimy=max_dims;
				break;
			case 'x':
				dimx++;
				if(dimx>max_dims) dimx=0;
				break;
			case 'y':
				dimy++;
				if(dimy>max_dims) dimy=0;
				break;
			case 'z': // swap apparent x/y
				i=dimy;
				dimy=dimx;
				dimx=i;
				break;
			case 'l':
				zz_mode=zz_selected_mode;
				zz_menu_choice=1; // link cell
				break;
			case 'c':
				zz_mode=zz_selected_mode;
				zz_menu_choice=0; // new cell
				break;
			case 'r':
				zz_mode=zz_selected_mode;
				zz_menu_choice=3; // remove cell
				break;
			case 'e':
				zz_mode=zz_selected_mode;
				zz_menu_choice=2; // edit content mode
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
			case 'h':
				shadowbox(5, 5, 30, 10, "HELP\nNavigation    Editing\n w            i-edit menu\na s           e-edit\n d            c-new\nx-inc dimx    r-remove\ny-inc dimy    l-link\nX-dec dimx    m-mark\nY-dec dimy    h-help\nPRESS ANY KEY TO CONTINUE", 0x20, 0x02);
				zz_mode=zz_delay_mode;
				break;
		}
		kb_buf=0;
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
			if(modality==6) { // new cell part 2: edit an empty cell's contents
					  // part 2 has to come before part 1 because of modality switches
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
					get_cell(currcell)->connections[dimlink][forelink]=get_cell(currcell_old)->connections[dimlink][forelink];
					get_cell(get_cell(currcell_old)->connections[dimlink][forelink])->connections[dimlink][!forelink]=currcell;
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
				if(zz_menu_choice==0 || modality==5) { // new cell part 1: connection designation
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
							get_cell(currcell)->start=currcell*max_edit_size;
							puts("Good! Now, compose your new cell.");
							modality=6;
	                                        	for (i=i; i<max_edit_size-2; i++) {
	                                                	editbuf[i]=0;
	                                        	}
	                                       		kb_buf=0;
						}
					}
				}
				if(zz_menu_choice==1 || modality==1) { // edit connections
					relink();
				}
				if(zz_menu_choice==2 || modality==2) { // edit contents
					int i;
					if(!modality) {
						modality=2;
						for(i=0; i<(get_cell(currcell)->end - get_cell(currcell)->start) && i<max_edit_size; i++) {
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
				if (zz_menu_choice==3) { // remove cell
					if (!modality) {
						display_cells();
						locate(0, 0);
						puts("Press wasd to choose direction or c to cancel");
						modality=3;
						yield();
					} else if (modality==3) {
						if(kb_buf=='c')
							modality=0;
							yield();
						if(kb_buf=='w' || kb_buf=='a' || kb_buf=='s' || kb_buf=='d') {
							if(kb_buf=='w') 
								currcell_old=get_cell(currcell)->connections[dimy][0];
							if(kb_buf=='a')
								currcell_old=get_cell(currcell)->connections[dimx][0];
							if(kb_buf=='s')
								currcell_old=get_cell(currcell)->connections[dimy][1];
							if(kb_buf=='d')
								currcell_old=get_cell(currcell)->connections[dimx][1];
							for(i=0; i<max_dims; i++) { // just make this neighbour nobody
								get_cell(get_cell(currcell_old)->connections[i][0])->connections[i][1]=get_cell(currcell_old)->connections[i][1];
								get_cell(get_cell(currcell_old)->connections[i][1])->connections[i][0]=get_cell(currcell_old)->connections[i][0];
							}
							modality=0;
						} else {
							kb_buf=0;
							yield();
						}
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

