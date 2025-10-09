// main.c - kernel entry point
// Ben Staehle - 8/18/25

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot2.h"
#include "video.h"
#include "terminal.h"
#include "idt.h"
#include "mmu.h"
#include "irq.h"
#include "keyboard.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kmain(uint32_t mb2_info_addr) {
	// parse the multiboot2 info struct
	parse_mb2_header(mb2_info_addr);

    // initialize memory
    mmu_init();

    // set the IDT
    idt_install();
	IRQ_init();

	// initialize video
	kvideo_init();
    term_init(WHITE, BLACK);

    kb_init();

    for (int i = 0; i < 61; ++i) {
        kprintf("%s : %d\n", "HELLO WORLD", i);
    }

	// loop forever
	for (;;);
}
