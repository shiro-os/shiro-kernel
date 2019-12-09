disk_load:
    pusha
    push dx

        mov ah, 0x02    ; set read function
        mov al, dh      ; set sector read count
        mov cl, 0x02    ; sector to read

        mov ch, 0x00
        mov dh, 0x00

        int 0x13
        jc disk_load
    
    pop dx
    cmp al, dh
    jne sect_error
    popa
    ret

disk_error:
        mov ebx, DISK_ERROR
        call print
        jmp $
sect_error:
        mov ebx, SECT_ERROR
        call print
        jmp $
disk_loop:
    jmp $

DISK_ERROR: db "[ERROR] - Disk read error", 0
SECT_ERROR: db "[ERROR] - Incorrect number of sectors read", 0

; Unused, removed to save space
; print_hex:
;     pusha
;     mov cx, 0

; hex_loop:
;     cmp cx, 4
;     je end

;     mov ax, dx
;     and ax, 0x000f
;     add al, 0x30
;     cmp al, 0x39
;     jle step2
;     add al, 7

; step2:
;     mov bx, HEX_OUT + 5
;     sub bx, cx
;     mov [bx], al
;     ror dx, 4

;     add cx, 1
;     jmp hex_loop

; end:
;     popa
;     ret

; HEX_OUT:
;     db '0x0000',0
