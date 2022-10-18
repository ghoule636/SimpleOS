#pragma once
#include <stdint.h>

void mem_cpy(uint8_t *to_address, uint8_t *from_address, int size);
void mem_set(uint8_t* dest, uint8_t val, uint32_t size);