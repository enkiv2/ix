#ifndef vga_h
#define vga_h
#define VGAX 80
#define VGAY 24
#define VGAADDR 0xB8000

typedef struct vgapair_t {
	char c;
	char attr;
} vgapair;

#ifdef vga_c
vgapair*** screen=(vgapair***)VGAADDR;
int cursorx;
int cursory;
char color;
#endif
#ifndef vga_c
extern vgapair*** screen;
extern int cursorx;
extern int cursory;
extern char color;
#endif

void shadowbox(int x, int y, int width, int height, char* text, int fg, int bg); //@ console graphics routine
const char* editpane(int x, int y, int width, int height, char* text, int maxlen, int fg, int bg); //@ edit box

void locate(int x, int y);
void write(char c);
void putch(char c);
void puts(char* c);
void scroll(int numlines);
void invertattr();
void setattr(char attr);
void cls();
#endif

