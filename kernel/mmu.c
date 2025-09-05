// mmu.c - defines functions for segmentation and paging
// Ben Staehle - 9/4/25
#include "mmu.h"

// NOTE:
// - limit must be no more than 20 bits
// - flags must be no more than 4 bits
void gdt_set_gate(int gate_no, uint32_t base, uint32_t limit, uint8_t acc, uint8_t flags) {
    if (limit > 0xFFFFF || flags > 0x0F) {
        return; // invlaid params
    }
    
    // set the gate
    gdt_gate_t *ptr = &gdt[gate_no];
    
    ptr->limit1 = limit & 0x0000FFFF;
    ptr->base1  = base  & 0x0000FFFF;
    ptr->base2  = base  & 0x00FF0000;
    ptr->acc_byte    = acc;
    ptr->limit2_flgs = (limit & 0x000F0000) | (flags);
    ptr->base3  = base  & 0xFF000000;
}

static void lgdt() {
    gdt_ptr.size = sizeof(gdt) - 1;
    gdt_ptr.offset = (uint32_t)&gdt;

    set_gdt(&gdt_ptr, KCODE_SEG, KDATA_SEG);
}

void mmu_init() {
    // set GDT gates
    gdt_set_gate(0, 0x0, 0x0, 0x0, 0x0);
    gdt_set_gate(1, 0x00000000, 0xFFFFF, 0x9A, 0xC);
    gdt_set_gate(2, 0x00000000, 0xFFFFF, 0x92, 0xC);

    lgdt();
}

