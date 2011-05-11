#ifndef idt_h
#define idt_h
#define MAX_IRQ 255 // this might not be correct
typedef unsigned short  uint16_t;
void doidt();
void default_handler();
extern void defaulthandler();
extern void IRQ1();

struct IDTDescr{
	uint16_t offset_1; // offset bits 0..15
	uint16_t selector; // a code segment selector in GDT or LDT
	unsigned int zero;      // unused, set to 0
	unsigned char type_attr; // type and attributes, see below
	uint16_t offset_2; // offset bits 16..31
};

struct IDTPtr {
	uint16_t size;
	struct IDTDescr* desc;
};



#endif
