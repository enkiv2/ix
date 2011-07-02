#ifndef zx_h
#define zx_h

#include <zz.h>

#define BF_MAXSTACK 127
#define BF_MAXINTERP 127

#ifdef zx_c
int zx_pid[BF_MAXINTERP]; //@ interp -> pid lookup
int zx_stacks[BF_MAXINTERP][BF_MAXSTACK]; 
int zx_curcell[BF_MAXINTERP];
int zx_dimx[BF_MAXINTERP];
int zx_dimy[BF_MAXINTERP];
int zx_dx[BF_MAXINTERP];
int zx_dy[BF_MAXINTERP];
int zx_sp[BF_MAXINTERP];
int zx_maxi; //@ max interpreter
#endif 
// zx_c

void zx_gonorth(int interp);	//@ chug negward on apparent y
void zx_gosouth(int interp);	//@ chug posward on apparent y
void zx_goeast(int interp);	//@ chug posward on apparent x
void zx_gowest(int interp);	//@ chug negward on apparent x
void zx_reflect(int interp);	//@ invert delta
void zx_rotx(int interp);	//@ chug dimx posward by stackv
void zx_roty(int interp);	//@ chug dimy posward by stackv
void zx_tramp(int interp);	//@ # character 'trampoline'
void zx_suicide(int interp);	//@ @ character 'die'
void zx_jump(int interp);	//@ tramp stackv times
void zx_nsif(int interp);	//@ | character 'north south if'
void zx_not(int interp);	//@ inverts stackv and repushes
void zx_gt(int interp);		//@ ` character 'greater than'
void zx_pop(int interp);	//@ $ character 'pop'
void zx_dup(int interp);	//@ : charcter 'duplicate'
void zx_swp(int interp);	//@ \ character 'swap'
void zx_clr(int interp);	//@ n character 'clear stack'
void zxinterp(int pid);		//@ interpreter mainloop


#endif 
// zx_h

