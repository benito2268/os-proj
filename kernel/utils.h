// utils.h - various kernel utilty functions
// Ben Staehle - 8/31/25
#pragma once

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi, eflags;
    uint32_t cr0, cr2, cr3, eip;

} regs_t;

extern void dump_regs(regs_t *r);

void panic(char *msg);
void cpu_relax();
