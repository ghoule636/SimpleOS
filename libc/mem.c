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