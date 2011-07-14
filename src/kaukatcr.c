#define kaukatcr_c
#include <system.h>
#include <kaukatcr.h>

int slurp(int pid, char* start, char* end, char* fn) {
	if(slurpcount[pid]==0) { // we're just starting
		slurpcount[pid]++;
	}
	if(!strcmp(get_cell(interp_ip[pid])->start+istream_begin,end)) { // do this one first in case start=end
		slurpcount[pid]--;
	} else if(!strcmp(get_cell(interp_ip[pid])->start+istream_begin, start)) {
		slurpcount[pid]++;
	}
	// todo: map cell to fn
	interp_ip[pid]=get_cell(interp_ip[pid])->connections[abs(interp_delta[pid])][0?abs(interp_delta[pid])==interp_delta[pid]:1];
	if (!slurpcount[pid]) 
		return interp_ip[pid];
	return 0;
}
