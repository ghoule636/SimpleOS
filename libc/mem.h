#pragma once
#include <stdint.h>
#include <stddef.h>

/**
 * @brief Temporary hard-coded value for mem location of our heap.
 * 
 */
extern uint32_t placement_addr;

void mem_cpy(uint8_t *to_address, uint8_t *from_address, int size);
void mem_set(uint32_t* dest, uint8_t val, uint32_t size);
uint32_t mallok_internal(size_t size, int align, uint32_t *phys_addr);
uint32_t mallok_a(uint32_t size);
uint32_t mallok_p(uint32_t size, uint32_t *phys_addr);
uint32_t mallok_ap(uint32_t size, uint32_t *phys_addr);
uint32_t mallok(uint32_t size);