#ifndef kb_h
#define kb_h

#include "io.h"
#include "vga.h"
#define kb_port 0x60
void handle_kb();
#ifndef kb_c
extern char kb_buf;
extern char kb_cmd;
#endif
#ifdef kb_c
char caps;
char kb_buf;
char mode;
char kb_cmd;
char kb_map[2][0x3a]={
	"\000\0001234567890-=\b\tqwertyuiop[]\n\000asdfghjkl;'`\000\\zxcvbnm,./\000\000 ",
	"\000\000!@#$%^&*()_+\b\tQWERTYUIOP{}\n\000ASDFGHJKL:\"~\000|ZXCVBNM<>?\000\000 "};
#endif

#endif
