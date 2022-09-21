[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; prints a null-terminated string pointed to by edx
print_string32:
    pusha
    mov edx, VIDEO_MEMORY   ; set edx to the start of vid mem

print_string_pm_loop:
    mov al, [ebx]           ; Store the char at EBX in AL
    mov ah, WHITE_ON_BLACK  ; Store the char attributes in ah

    cmp al, 0               ; check if we are at the end of the string.
    je end_print_32

    mov [edx], ax           ; Store the char and attributes into video memory

    add ebx, 1              ; move to next char in string
    add edx, 2              ; move to next char in video memory.

    jmp print_string_pm_loop

end_print_32:
    popa
    ret