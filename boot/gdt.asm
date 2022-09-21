; Define our GDT preparing for the switch to 32-bit protected mode.

gdt_start:

gdt_null:               ; First set up the first segment which must be 8 bytes of 0 (null)
    dd 0x0
    dd 0x0

gdt_code:               ; code segment descriptor
    dw 0xffff           ; limit (bits 0-15)
    dw 0x0              ; base (bits 0-15)
    db 0x0              ; more base lol (bits 16-23)
    ; 1st flags: (present)1 (privilege)00 (descriptor type)1 
    ; type flags: (code)1 (conforming)0  (readable)1 (accessed)0
    ; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0
    db 10011010b        ; flags 
    db 11001111b        ; flags + limit (bits 16-19)
    db 0x0              ; base (bits 24-31)

gdt_data:               ; data segment descriptor
    ; same as code segment except for the type flags:
    ; (code)0 (expand down)0 (writable)1 (accessed)0
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b        ; type flags
    db 11001111b
    db 0x0

gdt_end:                ; this and gdt_start are used to calculate the gdt size.

gdt_descriptor:
    dw gdt_end - gdt_start - 1          ; size of the gdt minus one
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start