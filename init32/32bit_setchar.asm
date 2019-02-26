[bits 32]

; esp+4 = char
; esp+8 = color
; esp+12 = x
; esp+16 = y

setchar:
.setchar_begin:
    pusha
    mov ecx, LINE_WIDTH
    mov eax, [ebx+12]
    mov edx, [ebx+16]
    imul edx, ecx         ; Multiply Y-Offset by Screen-Width
    add eax, edx          ; Add Y-Offset to X-Offset
    imul eax, 2

.setchar_main:
    mov edx, VIDEO_MEMORY
    add edx, eax

    mov ah, byte [ebx+8]
    mov al, byte [ebx+4]
    mov [edx], ax

.setchar_end:
    popa
    ret

