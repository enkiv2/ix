#ifndef kb_h
#define kb_h

#include "io.h"
#include "vga.h"

#define kb_port 0x60
void handle_kb();

#ifndef kb_c
extern char kb_buf;
extern char kb_cmd;
#endif // not kb.c

#ifdef kb_c
char caps;
char mode;
char kb_buf;
char kb_cmd;
#endif // kb.c

#endif
