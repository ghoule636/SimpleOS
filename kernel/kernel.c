#include "../drivers/ports.h"
#include "../drivers/screen.h"

// TODO clean this up and move the input/output to a different driver file.

void main() {

    int offset_from_vga = get_cursor();

    // write the output string to the current position and move the cursor.
    char output[12] = "Hello World!";
    char *vga = 0xb8000;
    for (int i = 0; i < 12; i+=1) {
        vga[offset_from_vga] = *(output + i); 
        vga[offset_from_vga + 1] = 0x0f; /* White text on black background */
        offset_from_vga += 2;
        set_cursor(offset_from_vga);
    }

}