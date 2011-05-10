#ifndef zz_h
#define zz_h

#include "vga.h"

#define max_dims 256	//@
#define max_cells 1000	//@
#define cells_begin 0x00100000	//@

#define zz_display_mode 0	//@
#define zz_edit_mode 1		//@
#define zz_selected_mode 2	//@
#define zz_newcell_mode 3	//@
#define zz_editcell_mode 4	//@

typedef struct zz_t {
	int connections[max_dims][2];
	int start; /* refer to istream indices */
	int end;
} zzcell;

#define istream_begin cells_begin + sizeof(zzcell) * max_cells

#ifdef zz_c
int maxcell;		//@ highest number cell allocated
int zz_mode;		//@ mode for UI state
int currcell;		//@ currently selected cell
int currcell_old;	//@ marked cell for linking
int dimlink;		//@ cached dimension for linking
int forelink;		//@ cached posward/backward for linking
int dimx;		//@ current x dimension
int dimy;		//@ current y dimension
#endif
void nav_cells();
void init_cells();
void display_cells();
zzcell* get_cell(int id);
void write_cell(zzcell* cell, int limit);
#endif
