#include "kernel_assert.h"

void kernel_assert_clear() //@
{
	char *fb = (char *)0xB8000;
	
	register int i;
	for (i = 0; i < 80 * 25; ++i)
	{
		fb[i << 1      ] = 0x00;
		fb[(i << 1) + 1] = 0x07;
	}
}

void kernel_assert_print(const char *str, unsigned int len, unsigned int start) //@
{
	char *fb = (char *)(0xB8000 + (start << 1));
	
	register int i;
	for (i = 0; i < len; ++i)
	{
		fb[i << 1      ] = str[i];
		fb[(i << 1) + 1] = 0x07;
	}
}

unsigned int kernel_assert_strlen(const char *str) //@
{
	register unsigned int i = 0;
	while (str[i] != 0) ++i;
	
	return i;
}

void kernel_assert(int testarg, const char *file, const char *line) //@
{
	//char *fb = 0xB8000;
	unsigned int location = 0;
	
	if (testarg == 0) //false
	{
		kernel_assert_clear();
		
		kernel_assert_print("ix: assert '", 12, location);
		location += 12;
		
		kernel_assert_print(file, kernel_assert_strlen(file), location);
		location += kernel_assert_strlen(file);
		
		kernel_assert_print(":", 1, location);
		location += 1;
		
		kernel_assert_print(line, kernel_assert_strlen(line), location);
		location += kernel_assert_strlen(line);
		
		kernel_assert_print("' failed. HLT", 13, location);
		location += 13;
		
		kernel_halt();
	}
}
