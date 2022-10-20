#include "mem.h"
#include <stdint.h>

/**
 * @brief Copies the data from the from address to the to address.
 * 
 * @param to_address Destination address
 * @param from_address Copy from address
 * @param size Size of data to be copied.
 */
void mem_cpy(uint8_t *to_address, uint8_t *from_address, int size) {
    for (int i = 0; i < size; i++) {
        to_address[i] = from_address[i];
    }
}

/**
 * @brief Fills an area of memory of given size with the given value.
 * 
 * @param dest Starting location of memory to fill.
 * @param val Value to fill memory with.
 * @param size Size of memory area to fill.
 */
void mem_set(uint8_t* dest, uint8_t val, uint32_t size) {
    uint8_t* temp = dest;
    for (uint32_t i = 0; i < size; i++) {
        *temp = val;
        temp++;
    }
}

/**
 * @brief Temporary hard-coded value for mem location of our heap.
 * 
 */
uint32_t placement_addr = 0x10000;

/**
 * @brief Simple malloc function that assumes you never need to free
 * memory and simply just continually allocates more memory from an initial spot
 * in mem.
 * 
 * @param size - Like normal malloc the size of memory requested.
 * @param align - Align to page
 * @param phys_addr - Actual physical address in memory not virtual.
 * @return uint32_t - Location of memory allocated.
 */
uint32_t mallok(size_t size, int align, uint32_t *phys_addr) {
    if (align == 1 && (placement_addr & 0xFFFFF000)) {
        placement_addr &= 0xFFFFF000;
        placement_addr += 0x1000;
    }
    if (phys_addr) {
        *phys_addr = placement_addr;
    }
    uint32_t tmp = placement_addr;
    placement_addr += size;
    return tmp;
}