[org 0x7c00]
    mov bp, 0x9000
    mov sp, bp

    call cls

    call print_nl

    mov bx, LOAD
    call print
    call print_nl

    mov bx, MSG_REAL_MODE
    call print

    call switch_to_pm

    jmp $

%include "bootsector/constants.asm"
%include "bootsector/bootsector_print.asm"
%include "init32/32bit_gdt.asm"
%include "init32/32bit_setchar.asm"
%include "init32/32bit_print.asm"
%include "init32/32bit_switch.asm"

LOAD:
    db '[INFO]  - Initiating Shiro Kernel...', 0

[bits 32]
    BEGIN_PM:
        mov ebx, MSG_PROT_MODE
        call print_string_pm
        jmp $

MSG_REAL_MODE db "[INFO]  - Started Shiro in 16-bit real mode", 0
MSG_PROT_MODE db "[INFO]  - Loaded Shiro 32-bit protected mode", 0

times 510-($-$$) db 0
dw 0xaa55
