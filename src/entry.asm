;
; entry.asm
;
;	(c) 2005 by Alexander Panek & Igor Galic
;

; Multiboot header
MULTIBOOT_PAGE_ALIGN   equ 1<<0
MULTIBOOT_MEMORY_INFO  equ 1<<1

MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
CHECKSUM               equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

align 4                         ;

MultibootHeader:                
	dd MULTIBOOT_HEADER_MAGIC   ;
	dd MULTIBOOT_HEADER_FLAGS   ;
	dd CHECKSUM                 ;

; globals
global entry                    ;
global gdt_pointer              ;
global gdt
; externs
extern kmain                    ;
extern flushGDT                 ;

stacksize equ 0x4000            ;

entry:
    cli                         ; first - to be sure - disable interrupts
    
    mov esp, stack + stacksize  ; set up stack pointer
	
    push eax					; magic value
	push ebx					; address of the multiboot information structure
    
    call flushGDT               ; ready?
                                ; set...
    call kmain					; go!

    hlt                         ; just in case someone
    for: jmp for                ; is doing something dirty!

section .bss                    ;
align 32                        ;

stack:
	resb stacksize              ; reserve stack area

section .data                   ;
gdt:
    dd 0x00000000               ; null descriptor
    dd 0x00000000               ; - 
    
    dd 0x0000FFFF               ; kernel code descriptor
    dd 0x00CF9A00               ; -
    
    dd 0x0000FFFF               ; kernel data descriptor
    dd 0x00CF9200               ; -
    
    ; TODO:
    ;.code_desc_modules:
    ;.data_desc_modules:
    ;.code_desc_user:
    ;.data_desc_user:
    
gdt_pointer:
    dw 0x17                     ; gdt limit [(3 * sizeof(GDTDescriptor)) - 1]
    dd gdt                      ; gdt base address

; vim: set ts=4 sw=4 et:
