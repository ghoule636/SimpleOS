#include "screen.h"
#include "ports.h"

// private functions
int get_cursor();
void set_cursor(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

int get_cursor() {
    /* Screen cursor position: ask VGA control register (0x3d4) for bytes
    * 14 = high byte of cursor and 15 = low byte of cursor. */
    port_byte_out(0x3d4, 14); /* Requesting byte 14: high byte of cursor pos */
    /* Data is returned in VGA data register (0x3d5) */
    int position = port_byte_in(0x3d5);
    position = position << 8; /* high byte */
    port_byte_out(0x3d4, 15); /* requesting low byte */
    
    position += port_byte_in(0x3d5);
    // VGA 'cells' consist of the character and its control data
    // so this means we have to multiply the position by two so we offset
    // the data and the control data.
    return position * 2;
}

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(0x3d4, 15);
    port_byte_out(0x3d5, offset);
    port_byte_out(0x3d4, 14);
    offset = offset >> 8;
    port_byte_out(0x3d5, offset);
}