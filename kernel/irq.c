// irq.c - defines a driver for the legacy PIC and code setting up IRQs
// Ben Staehle - 9/18/25
#include <stddef.h>

#include "irq.h"
#include "asm.h"
#include "idt.h"
#include "isr.h"
#include "mmu.h"

// define IRQ handlers
void (*IRQ_VECS[N_IRQS])(void) = { NULL };

void IRQ_issue_EOI(uint8_t irq) {
    if (irq >= 8) {
        // PIC2 was involved
        outb(PIC2_CMD, PIC_EOI);
    }

    outb(PIC1_CMD, PIC_EOI);
}

void IRQ_disable() {
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}

void IRQ_enable()  {
    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
}

void IRQ_init() {
    //initialize PICs and tell them ICW4 (init. control word) will be present
    outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // remap the PIC to avoid conflicts with INT16-31
    PIC_remap();

    // set the PICs to 8086 mode
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // install dummy IRQ handlers
    for (size_t irq = 0; irq < N_IRQS; ++irq) {
        idt_set_gate((uint8_t)(PIC1_OFFSET + irq), (uint32_t)isr_vecs[PIC1_OFFSET + irq], KCODE_SEG, 0x8E);
        IRQ_clr_mask((uint8_t)irq);  // pass 0..15 not 32..47
    }

    // enable IRQs
    sti();
}

void PIC_remap() {
    // remap the starting addresses
    outb(PIC1_DATA, PIC1_OFFSET);
    io_wait();
    outb(PIC2_DATA, PIC2_OFFSET);
    io_wait();

    // tell PIC1 and PIC2 that they are running in cascade mode
    outb(PIC1_DATA, 1 << CASCADE_IRQ);
    io_wait();
    outb(PIC2_DATA, CASCADE_IRQ);
    io_wait();
}

void IRQ_set_mask(uint8_t irq_line) {
    // is PIC1 or 2 responsible
    uint16_t port = irq_line < 8 ? PIC1_DATA : PIC2_DATA;

    // create the new mask and set it
    uint8_t mask = inb(port) | (1 << irq_line);
    outb(port, mask);
}

void IRQ_clr_mask(uint8_t irq_line) {
    // is PIC1 or 2 responsible
    uint16_t port = irq_line < 8 ? PIC1_DATA : PIC2_DATA;

    // create the new mask and set it
    uint8_t mask = inb(port) & ~(1 << irq_line);
    outb(port, mask);
}

void IRQ_install(uint8_t irq_no, void (*handler)(void)) {
    cli();

    // register an irq so it can be called from the trap() function
    if (irq_no > 15) {
        return;
    }

    // install the function
    IRQ_VECS[irq_no] = handler;

    sti();
}