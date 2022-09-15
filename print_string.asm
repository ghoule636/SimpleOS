; Function to print a string that terminates in a 0. String should be stored in bx
; By: Gabriel Houle
; 9/13/2022

; check value of bx. If its 0 end function popa and ret
; if its not then mov the value to al and print it.
; then increment address of bx and go back to the top of the loop.
print_string:
    pusha                   ; push all registers to the stack
    mov ah, 0x0e            ; BIOS tele-type function

    print_loop:
        mov al, [bx]        ; move the char to be checked into al
        cmp al, 0           ; check that it is not the terminating char
        je the_end          ; if so jump to the_end
        int 0x10            ; else: print the char
        add bx, 0x01        ; increment bx
        jmp print_loop      ; and then jump back to the top of the loop.

    the_end:
        popa
        ret