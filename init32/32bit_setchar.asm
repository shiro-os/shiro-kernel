[bits 32]

; ebx+0 = char
; ebx+1 = color
; ebx+2 = x
; ebx+3 = y

setchar:
.setchar_begin:
    pusha

.setchar_calcoffset:
    movzx edx, byte [ebx+2]
    movzx eax, byte [ebx+3]
    imul edx, 2             ; Multiply by 2 because of Color-Bytes
    imul eax, LINE_WIDTH    ; Multiply Y-Offset by Screen-Width
    add edx, eax            ; Add Y-Offset to X-Offset

.setchar_main:
    add edx, VIDEO_MEMORY   ; Add Video-Memory-Offset

    mov ax, word [ebx]
    mov [edx], ax

.setchar_end:
    popa
    ret
