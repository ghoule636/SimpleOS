#include "../drivers/screen.h"
#include "../cpu/descriptor_tables.h"
#include "../cpu/isr.h"

void main() {
    init_idt();
    irq_install();
}