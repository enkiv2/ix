/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Main.c: C code entry.
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include <system.h>

int pow(int x, int y) {
	int r;
	int i;
	
	r=1;
	for(i=0; i<=y; i++) {
		r=r*x;
	}
	return r;
}

char* padl(int count, char* buf, char fill) {
	int i;
	count-=strlen(buf);
	for(i=strlen(buf)+count; i>=count; i--) {
		buf[i]=buf[i-count];
	}
	for(i=0; i<count; i++) {
		buf[i]=fill;
	}
	return buf;
}

char* itoa(int in, char* buf) {
	int j, i, num;
	num=in;
	for(i=0; in>=pow(10, i); i++);
	if(in%10) i--;
	if(in==0) i=0;
	buf[i+1]='\0';
	for(j=0; i>=0; i--){
		if(in>0) {
			buf[j]='0'+(in/pow(10, i));
			in%=pow(10, i);
		} else {
			buf[j]='0';
		}
		j++;
	}
	if(in>10) in%=10;
	buf[j]='0'+in;
	j++;
	buf[j]='\0';
	j++;
	if(buf[0]=='0') { // get around glitch with extra preceding zeros
		for(i=1; i<j; i++)
			buf[i-1]=buf[i];
	}
	return buf;
}


void *memcpy(void *dest, const void *src, size_t count) { //@
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}

void *memset(void *dest, char val, size_t count) { //@
	char *temp = (char *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count) { //@
	unsigned short *temp = (unsigned short *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

size_t strlen(const char *str) { //@ 
	size_t retval;
	for(retval = 0; *str != '\0'; str++) retval++;
	return retval;
}

