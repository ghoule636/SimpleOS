#pragma once

#include "types.h"


typedef struct registers {
    u32int ds;          // Data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha
    u32int int_no, err_code;        // Interrupt number and error code
    u32int eip, cs, eflags, useresp, ss;// Pushed by processor automatically
} registers_t;

typedef void (*isr_t)(registers_t);

void isr_handler(registers_t r);

void isr_handler(registers_t r);

void register_interrupt_handler(u8int n, isr_t handler);

void irq_install();