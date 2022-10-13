#pragma once
#include "../cpu/types.h"

void mem_cpy(u8int *to_address, u8int *from_address, u32int size);
void mem_set(u8int* dest, u8int val, u32int size);