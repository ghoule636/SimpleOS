#pragma once
#include "../cpu/types.h"

void int_to_ascii(u32int n, char *str);
int ascii_to_int(char *str);
void reverseStr(char *s);
int strlen(char *s);
void append(char* buf, char c);
void backspace(char* str);
int strcmp(char* str1, char* str2);