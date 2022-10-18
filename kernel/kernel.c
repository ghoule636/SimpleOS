#include "../drivers/screen.h"
#include "../cpu/isr.h"

void kernel_main() {
    isr_install();
    irq_install();

    clear_screen();
    asm ("int $0x3");
    asm ("int $0x4");
}