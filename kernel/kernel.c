#include "../drivers/ports.h"

// TODO clean this up and move the input/output to a different driver file.

// function to move the cursor along with the output text.
void update_cursor(int offset) {
    offset /= 2;
    port_byte_out(0x3d4, 15);
    port_byte_out(0x3d5, offset);
    port_byte_out(0x3d4, 14);
    offset = offset >> 8;
    port_byte_out(0x3d5, offset);
}

void main() {
     /* Screen cursor position: ask VGA control register (0x3d4) for bytes
      * 14 = high byte of cursor and 15 = low byte of cursor. */
    port_byte_out(0x3d4, 14); /* Requesting byte 14: high byte of cursor pos */
    /* Data is returned in VGA data register (0x3d5) */
    int position = port_byte_in(0x3d5);
    position = position << 8; /* high byte */

    port_byte_out(0x3d4, 15); /* requesting low byte */
    position += port_byte_in(0x3d5);

    /* VGA 'cells' consist of the character and its control data
     * e.g. 'white on black background', 'red text on white bg', etc */
    int offset_from_vga = position * 2;

    // write the output string to the current position and move the cursor.
    char output[12] = "Hello World!";
    char *vga = 0xb8000;
    for (int i = 0; i < 12; i+=1) {
        vga[offset_from_vga] = *(output + i); 
        vga[offset_from_vga + 1] = 0x0f; /* White text on black background */
        offset_from_vga += 2;
        update_cursor(offset_from_vga);
    }

}