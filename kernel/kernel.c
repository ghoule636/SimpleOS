#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/descriptor_tables.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main() {
    init_idt();
    asm volatile("sti");
    // clear_screen();
    init_timer(50);
}