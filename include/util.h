#ifndef util_h
#define util_h

typedef int size_t;

extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern int pow(int, int);
extern char* itoa(int, char*);
extern char* padl(int, char*, char);

#endif
