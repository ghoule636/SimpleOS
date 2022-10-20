#pragma once
#include "../cpu/type.h"

void int_to_ascii(uint32_t n, char *str);
int ascii_to_int(char *str);
void hex_to_ascii(int n, char* str);
void reverseStr(char *s);
int strlen(char *s);
void append(char* buf, char c);
void backspace(char* str);
int strcmp(char* str1, char* str2);