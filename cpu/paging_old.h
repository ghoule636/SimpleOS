// #pragma once

// #include "isr.h"

// #include <stdint.h>

// typedef struct page {
//     uint32_t present    : 1;
//     uint32_t rw         : 1;
//     uint32_t user       : 1;
//     uint32_t accessed   : 1;
//     uint32_t dirty      : 1;
//     uint32_t unused     : 1;
//     uint32_t frame      : 1;
// } page_t;

// typedef struct page_table {
//     page_t pages[1024];
// } page_table_t;

// typedef struct page_directory {
//     page_table_t *tables[1024];

//     uint32_t tablesPhysical[1024];

//     uint32_t physicalAddr;
// } page_directory_t;

// void initialize_paging();

// void switch_page_directory(page_directory_t *newDir);

// page_t *get_page(uint32_t address, int make, page_directory_t *dir);

// void page_fault(registers_t *regs);

// #define PANIC(msg) panic(msg, __FILE__, __LINE__);
// extern void panic(char *message, char *file, uint32_t line);