#ifndef gdt_h
#define gdt_h

/* This defines what the stack looks like after an ISR was running */
struct regs {
        unsigned int gs, fs, es, ds;
        unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
        unsigned int int_no, err_code;
        unsigned int eip, cs, eflags, useresp, ss;    
};

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


#endif
