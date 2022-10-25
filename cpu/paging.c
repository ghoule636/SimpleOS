#include "paging.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));

uint32_t first_page_table[1024] __attribute__((aligned(4096)));


void initialize_paging() {
    //set each entry to not present
    int i;
    for(i = 0; i < 1024; i++)
    {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }
    
    //we will fill all 1024 entries in the table, mapping 4 megabytes
    for(i = 0; i < 1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
        first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
    }

    page_directory[0] = ((unsigned int)first_page_table) | 3;

    register_interrupt_handler(14, page_fault);

    asm volatile("mov %0, %%cr3":: "r"(&page_directory));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void page_fault(registers_t *regs) {
    uint32_t faulting_addr;
    char faulting_addr_str[255];

    asm ("mov %%cr2, %0": "=r" (faulting_addr));

    hex_to_ascii(faulting_addr, faulting_addr_str);
    int present = (regs->err_code & 0x1);
    int rw = regs->err_code & 0x2;
    int us = regs->err_code & 0x4;
    int reserved = regs->err_code & 0x8;
    int id = regs->err_code & 0x10;

    print("Page fault! ( ");
    if (present) {print("present ");}
    if (rw) {print("read-only ");}
    if (us) {print("user-mode ");}
    if (reserved) {print("reserved ");}
    if (id) {print("instruction fetch ");}
    print(") at ");
    print(faulting_addr_str);
    print("\n");
    // PANIC("Page fault");
}

// extern void panic(char *message, char *file, uint32_t line)
// {
//     // We encountered a massive problem and have to stop.
//     asm volatile("cli"); // Disable interrupts.

//     print("PANIC(");
//     print(message);
//     print(") at ");
//     print(file);
//     print(":");
//     char lineStr[255];
//     int_to_ascii(line, lineStr);
//     print(lineStr);
//     print("\n");
//     // Halt by going into an infinite loop.
//     for(;;);
// }