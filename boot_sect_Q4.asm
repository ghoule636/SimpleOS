;
; A boot sector that prints a string using my function.
;
[org 0x7c00]

mov bx, HELLO_MSG
call print_string       ; calls our lovely function to print the message.

mov bx, GOODBYE_MSG
call print_string

jmp $

%include "print_string.asm"

;Data
HELLO_MSG:
    db 'Hello, World!', 0 ; <-- 0 is the end char

GOODBYE_MSG: 
    db 'Goodbye!', 0

times 510-($-$$) db 0
dw 0xaa55