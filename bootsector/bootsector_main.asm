[org 0x7c00]
    KERNEL_OFFSET equ 0x1000
    mov [BOOT_DRIVE], dl

    mov bp, 0x9000
    mov sp, bp

    call cls
    call load_kernel
    call switch_to_pm

    jmp $

%include "bootsector/constants.asm"
%include "bootsector/bootsector_disk.asm"
%include "bootsector/bootsector_cls.asm"
%include "init32/32bit_gdt.asm"
%include "init32/32bit_print.asm"
%include "init32/32bit_switch.asm"

LOAD:
    db '[INFO]  - Initiating Shiro Kernel...', 0

[bits 16]
    load_kernel:
        mov bx, KERNEL_OFFSET
        mov dh, 2
        mov dl, [BOOT_DRIVE]
        call disk_load
        ret

[bits 32]
    BEGIN_PM:
        mov ebx, MSG_LOAD_KERNEL
        call print_string_pm
        call KERNEL_OFFSET
        mov ebx, MSG_EXEC_KERNEL
        call print_string_pm
        jmp $


BOOT_DRIVE db 0

MSG_LOAD_KERNEL db "[INFO]  - Loading kernel into memory", 0
MSG_EXEC_KERNEL db "[INFO] - Kernel execution was finished", 0

times 510-($-$$) db 0
dw 0xaa55
