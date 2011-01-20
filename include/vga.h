#ifndef vga_h
#define vga_h
#define VGAX 80
#define VGAY 24
#define VGAADDR 0xB8000

typedef struct vgapair_t {
	char c;
	char attr;
} vgapair;

//typedef vgapair[VGAX][VGAY] vgascreen;
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

void locate(int x, int y);
void write(char c);
void kprint(char* c);
void scroll(int numlines);
void setattr(char attr);
void cls();
#endif

