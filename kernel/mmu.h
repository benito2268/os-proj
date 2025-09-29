// mmu.h - defines functions for configuring the MMU
// Ben Staehle - 9/4/25
#pragma once

#define GDT_ENTRY_KCODE 1
#define GDT_ENTRY_KDATA 2

#define KCODE_SEG ((GDT_ENTRY_KCODE << 3) | 0)
#define KDATA_SEG ((GDT_ENTRY_KDATA << 3) | 0)

#define N_GDT_GATES 4

#ifndef __ASSEMBLER__
#include "types.h"

typedef struct __attribute__((packed)) {
    ushort limit1;
    ushort base1;
    ubyte base2;
    ubyte acc_byte;
    ubyte limit2_flgs;
    ubyte base3;
} gdt_gate_t;

typedef struct __attribute__((packed)) {
    ushort size;
    uint offset;
} gdtr_t;

static gdtr_t gdt_ptr;
static gdt_gate_t gdt[N_GDT_GATES];

extern void set_gdt(gdtr_t *addr, uint code_dsc, uint data_dsc);

void gdt_set_gate(int gate_no, uint base, uint limit, ubyte acc, ubyte flags);
void mmu_init();

#endif