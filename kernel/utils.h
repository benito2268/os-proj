// utils.h - various kernel utilty functions
// Ben Staehle - 8/31/25
#pragma once

#include <stdint.h>

typedef struct __attribute__((packed)) {
    

} regs_t;

void panic(char *msg);
void cpu_relax();
