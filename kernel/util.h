#pragma once

#include "../cpu/types.h"

void mem_cpy(u8int* from_address, u8int* to_address, u32int size);
void mem_set(u8int* dest, u8int val, u32int size);
void int_to_ascii(u32int n, u8int str[]);
int ascii_to_int(u8int str[]);
void reverseStr(char s[]);
int strlen(char s[]);