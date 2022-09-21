; A boot sector program that loads the kernel and enters 32-bit protected mode.
[org 0x7c00]
KERNEL_OFFSET equ 0x1000        ; Memory offset for loading the kernel

    mov [BOOT_DRIVE], dl        ; Store the boot drive

    mov bp, 0x9000              ; Initialize the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE       ; Announce booting from 16-bit real mode
    call print_string16
    call print_nl

    call load_kernel            ; Load the kernel

    call switch_to_pm           ; Switch to 32-bit protected mode

    jmp $

%include "print_string16.asm"
%include "print_hex.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string32.asm"
%include "switch_to_pm.asm"

[bits 16]

load_kernel:
    mov bx, MSG_LOAD_KERNEL     ; Announce we are loading the kernel
    call print_string16

    mov bx, KERNEL_OFFSET       ; Set-up for disk load routine
    mov dh, 15                  ; Load the first 15 sectors
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]

BEGIN_PM: 

    mov ebx, MSG_PROT_MODE      ; Announce we have entered 32-bit mode
    call print_string32

    call KERNEL_OFFSET          ; Jump to kernel code

    jmp $

; globals
BOOT_DRIVE: db 0
MSG_REAL_MODE: db 'Started in 16-bit Real Mode', 0
MSG_PROT_MODE: db 'Successfully landed in 32-bit Protected Mode', 0
MSG_LOAD_KERNEL: db "Loading kernel into memory.", 0

; bootsector padding and magic number.
times 510-($-$$) db 0
dw 0xaa55