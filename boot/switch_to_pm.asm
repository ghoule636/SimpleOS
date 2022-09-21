[bits 16]
; Switch to protected mode
switch_to_pm:

    cli                     ; turn off interrupts
    lgdt [gdt_descriptor]   ; Load our global descriptor table

    mov eax, cr0            ; set first bit of CR0 to switch to protected mode
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm    ; make a far jump to force the CPU to flush its cache

[bits 32]
; initialize registers and stack once in 32bit protected mode
init_pm:
    mov ax, DATA_SEG        ; Change our segment pointer registers to the
    mov ds, ax              ; data selector we defined in our GDT
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x9000         ; Update stack position
    mov esp, ebp

    call BEGIN_PM           ; return to calling function but don't return!
