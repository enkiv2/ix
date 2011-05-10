#ifndef zz_h
#define zz_h

#include "vga.h"

#define max_dims 256
#define max_cells 1000
#define cells_begin 0x00100000

#define zz_display_mode 0
#define zz_edit_mode 1

typedef struct zz_t {
	int connections[max_dims][2];
	int start; /* refer to istream indices */
	int end;
} zzcell;

#define istream_begin cells_begin + sizeof(zzcell) * max_cells

#ifdef zz_c
int zz_mode;
int currcell;
int currcell_old;
int dimx;
int dimy;
#endif
void nav_cells();
void init_cells();
void display_cells();
zzcell* get_cell(int id);
void write_cell(zzcell* cell, int limit);
#endif
