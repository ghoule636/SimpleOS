#include "../drivers/ports.h"
#include "../drivers/screen.h"

// TODO clean this up and move the input/output to a different driver file.

void main() {


    clear_screen();
    char output[12] = "Hello World!";
    print(output);

}