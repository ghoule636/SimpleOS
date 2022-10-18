; Ensures that we jump into the kernel's entry function.
global _start;
[bits 32]

_start:
    [extern kernel_main]; Lets the linker know to substitute the address of main
    call kernel_main
    jmp $