; requires '-fda' flag set when running qemu-system-x86_64
[org 0x7c00]

mov [BOOT_DRIVE], dl
call print_hex
call print_nl

mov bp, 0x8000                  ; Set the stack somewhere out of the way
mov sp, bp

mov bx, 0x9000                  ; Load 5 sectors to 0x0000(ES):0x9000(BX)
mov dh, 5
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]                ; print out the first loaded word, 0xdada
call print_hex

mov dx, [0x9000 + 512]          ; print out the second loaded word 0xface
call print_hex

jmp $

%include "print_string.asm"
%include "print_hex.asm"
%include "disk_load.asm"

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface