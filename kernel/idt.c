// idt.c - defines IDT and helper funcs
// Ben Staehle - 8/19/25

#include "idt.h"
#include "asm.h"

void idt_set_gate(uint8_t idx, uint32_t offset, uint16_t selector, uint8_t attribs) {
	idt_gate_t gate = {
		.offset = (uint16_t)(offset & OFFSET_LO_MASK),
		.selector = selector,
		.zero = IDT_GATE_NULL_BITS,
		.attribs = attribs,
		.offset2 = (uint16_t)(offset & OFFSET_HI_MASK)
	};

	idt[idx] = gate;
}

void idt_install() {
	idt_ptr.base = (uint32_t)(&idt);
	idt_ptr.limit = (sizeof(idt_gate_t) * N_IDT_GATES) - 1;

	//clear the idt
	for (int i = 0; i < N_IDT_GATES; ++i) {
		idt_set_gate(i, 0x0, 0x0, 0x0);
	}

	asm volatile (
			"lidtl (%0);"
			:: "r"(&idt_ptr)
	);
	
	// enable inturrupts
	sti();
}
