;
; Boot sector program that will print out a hardcoded hex value.
; Used for testing the print_hex function.
[org 0x7c00]

mov bp, 0x8000      ; sets the base of the stack above where BIOS
mov sp, bp          ; loads our boot sector

mov dx, 0x1fb6      ; declare hex value to be printed.
call print_hex

mov bx, HEX_OUT
call print_string

jmp $

%include "print_string.asm"
%include "print_hex.asm"

HEX_OUT: 
    db '0x0000',0

times 510-($-$$) db 0
dw 0xaa55