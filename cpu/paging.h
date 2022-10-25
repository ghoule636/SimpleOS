#pragma once

#include <stdint.h>
#include "isr.h"


void initialize_paging();
void page_fault(registers_t *regs);