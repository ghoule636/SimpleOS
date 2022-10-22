#include "paging.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

uint32_t *frames;
uint32_t nframes;

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

/**
 * @brief Set a bit in the frame.
 * 
 * @param frame_addr 
 */
static void set_frame(uint32_t frame_addr) {
    uint32_t frame = frame_addr / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr) {

}

static uint32_t test_frame(uint32_t frame_addr) {

}

static uint32_t first_frame() {

}

void alloc_frame(page_t *page, int is_kernel, int is_writable) {

}

void free_frame(page_t *page) {

}

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