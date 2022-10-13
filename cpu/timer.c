#include "timer.h"
#include "isr.h"
#include "descriptor_tables.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../libc/function.h"

u32int tick = 0;

static void timer_callback(registers_t regs) {
    UNUSED(regs);
    // tick++;
    // print("Tick: ");
    // char tick_ascii[256];
    // int_to_ascii(tick, tick_ascii);
    // print(tick_ascii);
    // print("\n");
}

/**
 * @brief This function sets up the PIT to interrupt the CPU at a specific 
 * frequency. We set it to be about 100Hz (once every 10ms).
 * 
 * 
 * The programmable interval timer is a chip connected to IRQ0.
 * It can interrupt the CPU at a user-defined rate (between 18.2Hz and 1.1931 MHz).
 * The PIT is the primary method used for implementing a system clock and the
 * only method available for implementing multitasking (switch processes on interrupt).
 * 
 * @param frequency 
 */
void init_timer(u32int frequency) {
    // Register timer callback as the IRQ0!
    register_interrupt_handler(IRQ0, &timer_callback);

    // This gets us our required frequency.
    u32int divisor = 1193180 / frequency;

    // Divisor is sent byte-wise so split into upper/lower bytes.
    u8int low = (u8int)(divisor & 0xFF);
    u8int high = (u8int)((divisor >> 8) & 0xFF);

    // Command byte for the PIT. '0x36' sets the PIT into repeating mode which
    // will refresh once the divisor counter reaches zero. '0x36' also tells the
    // PIT we want to set the divisor value.
    port_byte_out(0x43, 0x36);

    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
