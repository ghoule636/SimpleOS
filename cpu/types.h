#pragma once

typedef unsigned int    u32int;
typedef          int    s32int;
typedef unsigned short  u16int;
typedef          short  s16int;
typedef unsigned char   u8int;
typedef          char   s9int;

#define low_16(address) (u16int)((address) & 0xFFFF)
#define high_16(address) (u16int)(((address) >> 16) & 0xFFFF)
