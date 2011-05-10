global IRQ1;
global defaulthandler
extern handle_kb;
extern my_idt;
extern default_handler;

IRQ1:
	pushad;
	call handle_kb;
	popad;
	iret;
defaulthandler:
	iret;

