/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Global function declarations and type definitions
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "kernel_assert.h"
#include "vga.h"
#include "zz.h"
#include "io.h"


typedef int size_t;

/* This defines what the stack looks like after an ISR was running */
struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;    
};

// from util.c
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern int pow(int, int);
extern char* itoa(int, char*);
extern char* padl(int, char*, char);

// from gdt.c
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

// from idt.c
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

// from isrs.c
extern void isrs_install();

// from irq.c
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

// from timer.c
extern void timer_wait(int ticks);
extern void timer_install();
extern void displaytime();
extern int request_atomicity(int);
extern void yield();
extern int spawn(void(*fn)(int));
extern int fork();
extern void kill(int);
extern int renice(int, int);

// from kb.c
extern void keyboard_install();

#endif
