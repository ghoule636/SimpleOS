#include "../drivers/screen.h"
#include "../cpu/descriptor_tables.h"
#include "../cpu/isr.h"

void kernel_main() {
    init_idt();
    irq_install();
    clear_screen();
}