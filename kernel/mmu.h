// mmu.h - defines functions for configuring the MMU
// Ben Staehle - 9/4/25
#pragma once

/* System Memory Scheme
 * ================ 0x00000000 ================
 *          IDT, IO, BIOS THINGS - 1:1 MAP*
 * ================ 0x00200000 ================
 *          USER PROCESS MEMORY 
 * ================ 0xC0000000 ================
 *          KERNEL MEMORY
 * ================ 0xFFFFFFFF ================
 */

// segementation defs
#define GDT_ENTRY_KCODE 1
#define GDT_ENTRY_KDATA 2

#define KCODE_SEG ((GDT_ENTRY_KCODE << 3) | 0)
#define KDATA_SEG ((GDT_ENTRY_KDATA << 3) | 0)

#define N_GDT_GATES 4

// paging defs
#define PAGE_SIZE 0x1000 // 4kb

#define MEM_BASE  0x00000000
#define MEM_TOP   0xFFFFFFFF

#define IO_TOP    0x001FFFFF // first 2 MB contains IO and BIOS stuff 

#define KERN_BASE 0xC0000000

#define PG_PRESENT 0x00000001
#define PG_RW      0x00000002

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

// paging things

typedef uint pde_t;
typedef uint pte_t;

static pde_t page_directory[1024] = { 0 };

static pte_t first_2mb_pt[1024] = { 0 };
static pte_t framebuffer_pt[1024] = { 0 };

static gdtr_t gdt_ptr;
static gdt_gate_t gdt[N_GDT_GATES];

extern void set_gdt(gdtr_t *addr);
extern void enable_paging(pde_t *pd_addr);

void gdt_set_gate(int gate_no, uint base, uint limit, ubyte acc, ubyte flags);
void mmu_init();

#endif
