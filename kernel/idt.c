// idt.c - defines IDT and helper funcs
// Ben Staehle - 8/19/25

#include <stddef.h>

#include "idt.h"
#include "isr.h"
#include "mmu.h"
#include "asm.h"

// define the idt (globally)
idt_gate_t idt[N_IDT_GATES] __attribute__((aligned(16)));

void idt_set_gate(uint8_t idx, uint32_t offset, uint16_t selector, uint8_t attribs) {
	idt_gate_t gate = {
		.offset = (uint16_t)(offset & OFFSET_LO_MASK),
		.selector = selector,
		.zero = IDT_GATE_NULL_BITS,
		.attribs = attribs,
		.offset2 = (uint16_t)((offset & OFFSET_HI_MASK) >> 16),
	};

	idt[idx] = gate;
}

void idt_install() {
	idt_ptr.base = (uint32_t)(&idt);
	idt_ptr.limit = (sizeof(idt_gate_t) * N_IDT_GATES) - 1;

    // set up the first 32 exception ISRs
    for (size_t i = 0; i < 32; ++i) {
        idt_set_gate((uint8_t)i, (uint32_t)isr_vecs[i], KCODE_SEG, 0x8E); 
    }

	asm volatile (
		"lidtl (%0);"
		:: "r"(&idt_ptr)
	);

	// disable hardware IRQ's
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);

	// now safe to enable interrupts
	sti();
}
