; Ensures that we jump into the kernel's entry function.
[bits 32]
[extern main]       ; Lets the linker know to substitute the address of main

call main
jmp $