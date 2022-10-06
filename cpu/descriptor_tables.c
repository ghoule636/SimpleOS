#include "descriptor_tables.h"
#include "../kernel/util.h"
#include "../drivers/ports.h"

idt_entry_t idt_entries[IDT_ENTRIES_SIZE];
idt_ptr_t idt_ptr;

void set_idt_gate(u32int n, u32int handler) {
    idt_entries[n].base_lo = low_16(handler);
    idt_entries[n].base_hi = high_16(handler);
    idt_entries[n].sel = KERNEL_CS;
    idt_entries[n].always0 = 0;
    idt_entries[n].flags = 0x8E;
}

void init_idt() {
    idt_ptr.base = (u32int)&idt_entries;
    idt_ptr.limit = IDT_ENTRIES_SIZE * sizeof(idt_entry_t) - 1;

    // mem_set(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    set_idt_gate(0, (u32int)isr0);
    set_idt_gate(1, (u32int)isr1);
    set_idt_gate(2, (u32int)isr2);
    set_idt_gate(3, (u32int)isr3);
    set_idt_gate(4, (u32int)isr4);
    set_idt_gate(5, (u32int)isr5);
    set_idt_gate(6, (u32int)isr6);
    set_idt_gate(7, (u32int)isr7);
    set_idt_gate(8, (u32int)isr8);
    set_idt_gate(9, (u32int)isr9);
    set_idt_gate(10, (u32int)isr10);
    set_idt_gate(11, (u32int)isr11);
    set_idt_gate(12, (u32int)isr12);
    set_idt_gate(13, (u32int)isr13);
    set_idt_gate(14, (u32int)isr14);
    set_idt_gate(15, (u32int)isr15);
    set_idt_gate(16, (u32int)isr16);
    set_idt_gate(17, (u32int)isr17);
    set_idt_gate(18, (u32int)isr18);
    set_idt_gate(19, (u32int)isr19);
    set_idt_gate(20, (u32int)isr20);
    set_idt_gate(21, (u32int)isr21);
    set_idt_gate(22, (u32int)isr22);
    set_idt_gate(23, (u32int)isr23);
    set_idt_gate(24, (u32int)isr24);
    set_idt_gate(25, (u32int)isr25);
    set_idt_gate(26, (u32int)isr26);
    set_idt_gate(27, (u32int)isr27);
    set_idt_gate(28, (u32int)isr28);
    set_idt_gate(29, (u32int)isr29);
    set_idt_gate(30, (u32int)isr30);
    set_idt_gate(31, (u32int)isr31);

    // Remap the PIC
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 

    // Install the IRQs
    set_idt_gate(32, (u32int)irq0);
    set_idt_gate(33, (u32int)irq1);
    set_idt_gate(34, (u32int)irq2);
    set_idt_gate(35, (u32int)irq3);
    set_idt_gate(36, (u32int)irq4);
    set_idt_gate(37, (u32int)irq5);
    set_idt_gate(38, (u32int)irq6);
    set_idt_gate(39, (u32int)irq7);
    set_idt_gate(40, (u32int)irq8);
    set_idt_gate(41, (u32int)irq9);
    set_idt_gate(42, (u32int)irq10);
    set_idt_gate(43, (u32int)irq11);
    set_idt_gate(44, (u32int)irq12);
    set_idt_gate(45, (u32int)irq13);
    set_idt_gate(46, (u32int)irq14);
    set_idt_gate(47, (u32int)irq15);

    idt_flush((u32int)&idt_ptr);
}