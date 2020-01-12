OUTPUT_FORMAT(binary);
OUTPUT_ARCH(i386:x86-64);
ENTRY(_entry);

SECTIONS{
    . = 0x1000;
    .text : {
        _text = .;
        *(.text)
    }

   .data : {
        _data = .;
        *(.data)
    }

    .rodata :  {
        _rodata = .;
        *(.rodata)
    }

   .bss : {
       *(.bss)
    }
}
