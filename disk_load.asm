; Sector loading utility program. 
disk_load:
    pusha
    push dx

    mov ah, 0x02            ; BIOS read sector function

    mov al, dh              ; Read dh sectors
    mov ch, 0x00            ; Select cylinder 0
    mov dh, 0x00            ; Select the head 0 (base 0)
    mov cl, 0x02            ; Select the sector after the boot sector(2nd)(base 1... wtf)

    ; mov bx, 0xa000          ; Indirectly set es
    ; mov es, bx
    ; mov bx, 0x1234          
    ; Data will be read to 0xa000:0x1234, which the CPU will translate to physical address 0xa1234

    int 0x13                ; BIOS interrupt for the read sector function
    jc disk_error_carry     ; Jump if carry flag was set which signals a general fault.

    ; Checking number of sectors read
    pop dx                  ; restore dx from stack
    cmp dh, al              ; if al (sectors read) != dh (sectors expected)
    jne disk_error_read
    popa
    ret

disk_error_carry:
    mov bx, DISK_ERROR_CARRY_MSG
    call print_string
    call print_nl
    mov dh, ah              ; https://stanislavs.org/helppc/int_13-1.html for list of error codes
    call print_hex
    jmp disk_loop

disk_error_read:
    mov bx, DISK_ERROR_READ_MSG
    call print_string
    jmp disk_loop

disk_loop:
    jmp $

DISK_ERROR_CARRY_MSG: 
    db "Disk read carry error!", 0

DISK_ERROR_READ_MSG: 
    db "Disk read error!", 0