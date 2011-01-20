.global kernel_halt
	.type kernel_halt, @function

kernel_halt:
	cli
haltjmp:
	hlt
	jmp haltjmp
