OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)

ENTRY(entry)
SECTIONS
{
    . = 0x1100000 + SIZEOF_HEADERS;

    /* text/read-only data */
    .text :	{ *(.text .gnu.linkonce.t.*) } =0x9090

    .rodata : { *(.rodata) }

    /* writable data  */
    . = ALIGN(0x1000);
    __data_start = .;
    .data : { *(.data .gnu.linkonce.d.*) }

    .dynamic : { *(.dynamic) }
    
    /* unintialized data (in same segment as writable data) */
    __bss_start = .;
    .bss : { *(.bss) }

    . = ALIGN(0x1000);
    _end = . ;

    /* Strip unnecessary stuff */
    /DISCARD/ : { *(.comment .note .eh_frame)  } 
}


