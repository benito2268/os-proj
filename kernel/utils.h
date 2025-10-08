// utils.h - various kernel utilty functions
// Ben Staehle - 8/31/25
#pragma once

#include "isr.h"
#include <stdint.h>
#include <stdbool.h>

// set and clear bits
#define SET_BIT(value, pos)    ((value) |= ((typeof(value))1 << (pos)))
#define CLEAR_BIT(value, pos)  ((value) &= ~((typeof(value))1 << (pos)))
#define TOGGLE_BIT(value, pos) ((value) ^= ((typeof(value))1 << (pos)))
#define IS_BIT_SET(value, pos) (((value) >> (pos)) & 1)

typedef struct __attribute__((packed)) {
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi, eflags;
    uint32_t cr0, cr2, cr3, eip;

} regs_t;

extern void dump_regs(regs_t *r);

void panic(const char *msg, bool is_trap, trap_frame_t *f);
void cpu_relax();
