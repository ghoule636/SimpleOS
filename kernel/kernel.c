#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/paging.h"

void kernel_main() {
    isr_install();
    irq_install();

    clear_screen();

    initialize_paging();
    print("hello world!");
    // asm ("int $0x3"); // trigger interrupts for testing the ISRs.
    // asm ("int $0x4");
}