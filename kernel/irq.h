// irq.h - defines code for the legacy PIC and setting up IRQs
// Ben Staehle - 9/18/25
#pragma once

#include <stdint.h>

#define N_IRQS 16

// PIC port numbers
#define PIC1      0x20
#define PIC2      0xA0
#define PIC1_CMD  0x20
#define PIC2_CMD  0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

// PIC commands
#define PIC_EOI      0x20
#define ICW1_INIT    0x10  // init command
#define ICW1_SINGLE  0x02  // sets cascading mode
#define ICW1_INTVL4  0x04
#define ICW1_LEVEL   0x08  // sets level (edge) trigger mode
#define ICW1_ICW4    0x01  // indicates icw4 will be present

#define ICW4_8086    0x01  // sets PIC to 8086 mode
#define ICW4_AUTO    0x02  // expect normal (auto) EOIs
#define ICW4_BUF_S   0x08  // sets buffered mode for pic2
#define ICW4_BUF_M   0x10  // sets buffered mode for pic1

#define CASCADE_IRQ  0x02

#define PIC1_OFFSET  0x20  // remap PIC1 to INT32
#define PIC2_OFFSET  0x28  // remap PIC2 to INT40

// registered IRQ handler functions
// if an entry is NULL that IRQ will do nothing (and cause no error)
extern void (*IRQ_VECS[N_IRQS])(void);

// public functions
void IRQ_issue_EOI(uint8_t irq);
void IRQ_init();

void IRQ_enable();
void IRQ_disable();

void IRQ_set_mask(uint8_t irq_line);
void IRQ_clr_mask(uint8_t irq_line);

void IRQ_install(uint8_t irq_no, void (*hander)(void));

// private functions
void PIC_remap();