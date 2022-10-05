#pragma once

#include "../cpu/types.h"

unsigned char port_byte_in(u16int port);
void port_byte_out (u16int port, u8int data);
unsigned short port_word_in (u16int port);
void port_word_out (u16int port, u16int data);