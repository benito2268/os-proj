// mmu.h - defines functions for configuring the MMU
// Ben Staehle - 9/4/25
#pragma once

#include <stdint.h>

#define GDT_ENTRY_KCODE 1
#define GDT_ENTRY_KDATA 2

#define KCODE_SEG ((GDT_ENTRY_KCODE << 3) | 0)
#define KDATA_SEG ((GDT_ENTRY_KDATA << 3) | 0)

#define N_GDT_GATES 4

typedef struct __attribute__((packed)) {
    uint16_t limit1;
    uint16_t base1;
    uint8_t base2;
    uint8_t acc_byte;
    uint8_t limit2_flgs;
    uint8_t base3;
} gdt_gate_t;

typedef struct __attribute__((packed)) {
    uint16_t size;
    uint32_t offset;
} gdtr_t;

static gdtr_t gdt_ptr;
static gdt_gate_t gdt[N_GDT_GATES];

extern void set_gdt(gdtr_t *addr, uint32_t code_dsc, uint32_t data_dsc);

void gdt_set_gate(int gate_no, uint32_t base, uint32_t limit, uint8_t acc, uint8_t flags);
void mmu_init();
