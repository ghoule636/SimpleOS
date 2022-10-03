#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "util.h"

void main() {
    clear_screen();

    /* Fill up the screen */
    for (int i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        print_at(str, 0, i);
    }

    char* test1 = "15\0";
    char* test2 = "30\0";

    int test1Int = ascii_to_int(test1);
    int test2Int = ascii_to_int(test2);
    print("\n");
    char str[255];
    int_to_ascii(test1Int+test2Int, str);
    print(str);
    print("\n");

    print("This text forces the kernel to scroll. Row 0 will disappear. ");
    print("And with this text, the kernel will scroll again, and row 1 will disappear too!");
}