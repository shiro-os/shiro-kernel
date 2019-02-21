[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

LINE_OFFSET db 0xA0 ; Magic
OFFSET_COUNT db 0x03 ; Start at the third line

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_calcOffset:
    push eax
    push ebx

    movzx eax, byte [LINE_OFFSET]
    movzx ebx, byte [OFFSET_COUNT]
    imul eax, ebx
    add edx, eax

    pop ebx
    pop eax

print_string_pm_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    cmp al, 0
    je print_string_pm_done

    mov [edx], ax
    add ebx, 1
    add edx, 2

    jmp print_string_pm_loop

print_string_pm_done:
    inc byte [OFFSET_COUNT]
    popa
    ret
