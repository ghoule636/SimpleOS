#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/descriptor_tables.h"
#include "../cpu/isr.h"

void main() {
    init_idt();
    clear_screen();
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
}