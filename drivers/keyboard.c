#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/function.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define ESC 0x1
#define SCANCODE_MAX 57

static char key_buffer[256];

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);

    if (scancode > SCANCODE_MAX) return;
    if (scancode == BACKSPACE) {
        if (strlen(key_buffer) > 0) {
            print_backspace();
            backspace(key_buffer);
        }
    } else if (scancode == ENTER) {
        print("\n");
        if (strcmp(key_buffer, "EXIT") == 0) {
            print("Halting the CPU!");
            asm volatile("hlt");
        } else if(strcmp(key_buffer, "PAGE") == 0) {
            char hexVal[255];
            int pointer;
            print("Allocating memory at: \n");
            pointer = mallok_a(0x1000);
            hex_to_ascii(pointer, hexVal);
            print(hexVal);
            print("\n");
            hexVal[0] = 0;
        } else if(strcmp(key_buffer, "ALLOC") == 0) {
            char hexVal[255];
            int pointer;
            print("Allocating memory at: \n");
            pointer = mallok(sizeof(int));
            hex_to_ascii(pointer, hexVal);
            print(hexVal);
            print("\n");
            hexVal[0] = 0;
        }
        key_buffer[0] = 0;
    } else if (scancode == ESC) {
        key_buffer[0] = 0;
        clear_current_row();
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        print(str);
        append(key_buffer, letter);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}