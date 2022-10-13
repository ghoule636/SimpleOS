#include "mem.h"
#include "../cpu/types.h"

/**
 * @brief Copies the data from the from address to the to address.
 * 
 * @param to_address Destination address
 * @param from_address Copy from address
 * @param size Size of data to be copied.
 */
void mem_cpy(u8int *to_address, u8int *from_address, u32int size) {
    for (u32int i = 0; i < size; i++) {
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
void mem_set(u8int* dest, u8int val, u32int size) {
    u8int* temp = dest;
    for (u32int i = 0; i < size; i++) {
        *temp = val;
        temp++;
    }
}