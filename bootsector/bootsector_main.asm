[org 0x7c00]

mov bx, LOAD
call print

call print_nl

mov dx, 0x12fe

jmp $

%include "bootsector/bootsector_print.asm"

LOAD:
    db 'Initiating Shiro Kernel...', 0

times 510-($-$$) db 0
dw 0xaa55
