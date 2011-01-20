global IRQ1;
extern handle_kb;
extern my_idt;

IRQ1:
	pushad;
	call handle_kb;
	popad;
	iret;

