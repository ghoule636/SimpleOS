#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main() {
    clear_screen();
    // print("Hello World!\n");

    // for (int i = 0; i < MAX_COLUMNS * MAX_ROWS - 1; i++){
    //     print("1");
    // }
    
    // for (int i = 0; i < MAX_COLUMNS; i++) {
    //     print("2");
    // }
    // for (int i = 0; i < MAX_COLUMNS; i++) {
    //     print("3");
    // }

    /* Fill up the screen */
    int i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        print_at(str, 0, i);
    }

    print_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    print("And with this text, the kernel will scroll again, and row 1 will disappear too!");
}