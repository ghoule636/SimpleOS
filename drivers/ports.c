#include "ports.h"

unsigned char port_byte_in(u16int port) {
    unsigned char result;
    // Reads a byte from the specified port
    // "=a" (result): put AL register in variable RESULT
    // "d" (port): loads EDX with port
    __asm__("in %%dx, %%al": "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (u16int port, u8int data) {
    // "a" (data): load EAX with data
    // "d" (port): loads EDX with port
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (u16int port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (u16int port, u16int data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
} 