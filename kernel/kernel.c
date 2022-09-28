#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main() {
    clear_screen();
    // print("Hello World!\n");

    for (int i = 0; i < MAX_COLUMNS * MAX_ROWS - 1; i++){
        print("1");
    }
    
    for (int i = 0; i < MAX_COLUMNS; i++) {
        print("2");
    }
    for (int i = 0; i < MAX_COLUMNS; i++) {
        print("3");
    }
}