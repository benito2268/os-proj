// main.c - kernel entry point
// Ben Staehle - 8/18/25

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "asm.h"
#include "multiboot2.h"
#include "video.h"
#include "terminal.h"
#include "utils.h"
#include "idt.h"
#include "mmu.h"
#include "irq.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

volatile int cnt = 0;
void test_irq(void) {
	cnt++;
}

void wait_for_irq0() {
	int start = cnt;
	while (cnt == start) {
		EMPTY_LOOP;
	}
}
   
void kmain(uint32_t mb2_info_addr) {
	// parse the multiboot2 info struct
	parse_mb2_header(mb2_info_addr);

    // initialize memory
    mmu_init();

    // set the IDT
    idt_install();
	IRQ_init();

	// register IRQ0
	//IRQ_install(0, &test_irq);

	// initialize video
	kvideo_init();
    term_init(WHITE, BLACK);

	kprintf("WAITING FOR TICK...\n");
	//wait_for_irq0();
	kprintf("GOT ONE! %d\n", cnt);

	// loop forever
	for (;;);
}
