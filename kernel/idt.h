// idt.h - defines IDT and helper funcs
// Ben Staehle - 8/19/25
#pragma once

#include <stdint.h>

#define N_IDT_GATES 256

#define OFFSET_LO_MASK 0x0000FFFF
#define OFFSET_HI_MASK 0xFFFF0000

#define IDT_GATE_NULL_BITS     0x00
#define INT_GATE_ATTRIBS_DLP0  0x8E
#define TRAP_GATE_ATTRIBS_DPL0 0x8F

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} idtr_t;

typedef struct __attribute__((packed)) {
   uint16_t offset;
   uint16_t selector;
   uint8_t zero;
   uint8_t attribs;
   uint16_t offset2;
} idt_gate_t;

static idtr_t idt_ptr;
extern idt_gate_t idt[N_IDT_GATES];

void idt_install();
void idt_set_gate(uint8_t idx, uint32_t offset, uint16_t selector, uint8_t attribs);
