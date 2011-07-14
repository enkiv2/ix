#ifndef _kaukatcr_h_
#define _kaukatcr_h_
#include <system.h>
#include <zz.h>

#ifdef kaukatcr_c
int interp_ip[MAX_PROCESSES]; //@ Cell ID for the current instruction
int interp_dictptr[MAX_PROCESSES]; //@ Cell ID for the top of the dictionary
int interp_sp[MAX_PROCESSES]; //@ Cell ID for the top of the stack
signed int interp_delta[MAX_PROCESSES]; //@ Dim number, signed
int slurpcount[MAX_PROCESSES]; //@ for internal use only
#endif

int slurp(int pid, char* start, char* end, char* fn);


#endif

