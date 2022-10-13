#include "keyboard.h"
#include "ports.h"
#include "../cpu/descriptor_tables.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/function.h"
#include "../libc/string.h"

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

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8int scancode = port_byte_in(0x60);

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