#ifndef _kaukatcr_h_
#define _kaukatcr_h_
#include <system.h>
#include <zz.h>

int interp_ip[MAX_PROCESSES]; //@ Cell ID for the current instruction
int interp_dictptr[MAX_PROCESSES]; //@ Cell ID for the top of the dictionary
int interp_sp[MAX_PROCESSES]; //@ Cell ID for the top of the stack

#endif

