;
;	gdt.asm
;
;		(c) 2005 by Alexander Panek & Igor Galic
;

; globals
global flushGDT                 ;

; externs
extern gdt_pointer              ;

flushGDT:
    lgdt [gdt_pointer]          ; store the gdt_pointer in GDTR
    jmp 0x08:flush              ; jump to the new code segment (0x08 = GDT offset)
flush:
    mov ax, 0x10                ; re-set the segment registers
    mov ds, ax                  ;
    mov es, ax                  ;
    mov fs, ax                  ;
    mov gs, ax                  ;
    mov ss, ax                  ;
    ret                         ; go back..obviously.
 
; vim: set ts=4 sw=4 et:
