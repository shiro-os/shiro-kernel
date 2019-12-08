OUTPUT_FORMAT(binary);
OUTPUT_ARCH(i386:x86-64);
ENTRY(_entry);

SECTIONS{
    . = 0x0;
    .text : {
        *(.text)
    }

    . = 0x0;
   .data : {
        *(.data)
    }

   .bss : {
       *(.bss)
    }
}