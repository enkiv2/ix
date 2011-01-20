#ifndef idt_h
#define idt_h

void doidt();
extern void IRQ1();
struct IDTDescr{
   unsigned char offset_1[2]; // offset bits 0..15
   unsigned char selector[2]; // a code segment selector in GDT or LDT
   unsigned int zero;      // unused, set to 0
   unsigned char type_attr; // type and attributes, see below
   unsigned char offset_2[2]; // offset bits 16..31
};



#endif
