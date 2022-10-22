#include "paging.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"

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
    uint32_t frame = frame_addr / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

// static uint32_t test_frame(uint32_t frame_addr) {
//     uint32_t frame = frame_addr / 0x1000;
//     uint32_t idx = INDEX_FROM_BIT(frame);
//     uint32_t off = OFFSET_FROM_BIT(frame);
//     return (frames[idx] & (0x1 << off));
// }

static uint32_t first_frame() {
    uint32_t i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
        if (frames[i] != 0xFFFFFFFF) {
            for (j = 0; j < 32; j++) {
                uint32_t toTest = 0x1 << j;
                if (!(frames[i]&toTest)) {
                    return i * 4 * 8 + j;
                }
            }
        } 
    }
    return 0;
}

void alloc_frame(page_t *page, int is_kernel, int is_writable) {
    if (page->frame != 0) {
        return;
    } else {
        uint32_t index = first_frame();
        if (index == (uint32_t)-1) {

        }
        set_frame(index * 0x1000);
        page->present = 1;
        page->rw = (is_writable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = index;
    }
}

void free_frame(page_t *page) {
    uint32_t frame;
    if (!(frame = page->frame)) {
        return;
    } else {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void initialize_paging() {
    // The size of physical memory. For the moment we 
    // assume it is 16MB big.
    uint32_t mem_end_page = 0x1000000;
    
    nframes = mem_end_page / 0x1000;
    frames = (uint32_t*)mallok(INDEX_FROM_BIT(nframes));
    mem_set(frames, 0, INDEX_FROM_BIT(nframes));
    
    // Let's make a page directory.
    kernel_directory = (page_directory_t*)mallok_a(sizeof(page_directory_t));
    current_directory = kernel_directory;

    // We need to identity map (phys addr = virt addr) from
    // 0x0 to the end of used memory, so we can access this
    // transparently, as if paging wasn't enabled.
    // NOTE that we use a while loop here deliberately.
    // inside the loop body we actually change placement_address
    // by calling mallok(). A while loop causes this to be
    // computed on-the-fly rather than once at the start.
    uint32_t i = 0;
    while (i < placement_addr)
    {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }
    // Before we enable paging, we must register our page fault handler.
    register_interrupt_handler(IRQ14, page_fault);

    // Now, enable paging!
    switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir) {
    current_directory = dir;
    asm ("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir) {
    // Turn the address into an index.
    address /= 0x1000;
    // Find the page table containing this address.
    uint32_t table_idx = address / 1024;
    if (dir->tables[table_idx]) // If this table is already assigned
    {
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else if(make)
    {
        uint32_t tmp;
        dir->tables[table_idx] = (page_table_t*)mallok_ap(sizeof(page_table_t), &tmp);
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else
    {
        return 0;
    }
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
}