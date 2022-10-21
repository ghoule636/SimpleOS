#include "paging.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void initialize_paging() {

}

void switch_page_directory(page_directory_t *newDir) {

}

page_t *get_page(uint32_t address, int make, page_directory_t *dir) {

}

void page_fault(registers_t regs) {
    uint32_t faulting_addr;
    char faulting_addr_str[255];

    asm ("mov %%cr2, %0": "=r" (faulting_addr));

    hex_to_ascii(faulting_addr, faulting_addr_str);
    int present = (regs.err_code & 0x1);
    int rw = regs.err_code & 0x2;
    int us = regs.err_code & 0x4;
    int reserved = regs.err_code & 0x8;
    int id = regs.err_code & 0x10;

    print("Page fault! ( ");
    if (present) {print("present ");}
    if (rw) {print("read-only ");}
    if (us) {print("user-mode ");}
    if (reserved) {print("reserved ");}
    print(") at ");
    print(faulting_addr_str);
    print("\n");
}