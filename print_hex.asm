; Function to print a 16 bit hex value. Prints the value stored in dx.
; By: Gabriel Houle
; 9/13/2022

; Need to convert a hex value into a string.
; The idea I have is to take 0x000f and use the 'and' command
; to bitmask the hex value giving me the first digit of the hex.
; Then add 30 to convert to an ASCII char and more if a letter.
; Then calculate the address we need to append to in HEX_OUT.
print_hex:
    pusha
    mov cx, 0                           ; the loop counter
    convert_loop:
        cmp cx, 4                       ; we need to loop 4 times since there are 4 hex chars
        je end_print_hex                ; end the loop

        ; store the value of dx in ax and then bitmask it and shift to an ASCII value.
        mov ax, dx
        and ax, 0x000f
        add al, 0x30
        cmp al, 0x39                    ; if the value is a letter then we need to add 8 before continuing
        jle store_char
        add al, 7

    store_char:
        ; get the addr of the HEX_OUT string.
        mov bx, HEX_OUT + 5
        sub bx, cx                      ; shift the value back by the current index
        ; then move the char stored at ax into the addr that bx is now pointing at.
        mov [bx], al
        ror dx, 4

        ; increment counter by 1 and then loop
        add cx, 1   
        jmp convert_loop

    end_print_hex:
        mov bx, HEX_OUT
        call print_string
        popa
        ret

HEX_OUT: 
    db '0x0000', 0