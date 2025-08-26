// isr.h - defines inturrupt service routines 0-31
// Ben Staehle - 8/19/25
#pragma once

#include <stdint.h>

static const char *isr_msgs[32] = {
   "Divide by Zero",
   "Debug Exception",
   "NMI",
   "Breakpoint",
   "Overflow",
   "Bound Range Exceeded",
   "Invalid Opcode",
   "Device Not Available",
   "Double Fault",
   "Coprocessor Segment Overrun",
   "Invalid TSS",
   "Segment Not Present",
   "Stack Segment Fault",
   "General Protection Fault",
   "Page Fault",
   "Reserved",
   "x87 Floating Point Error",
   "Alignment Check",
   "Machine Check",
   "SIMD Floating Point Exception",
   "Virtualization Exception",
   "Control Protection Exception",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
};

typedef struct __regs__ {
   uint32_t ds;
   uint32_t edi, esi, ebp, esp, ebx, ecx, eax;
   uint32_t int_no, err_no;
   uint32_t eip, cs, eflags, useresp, ss;
} regs_t;

void isr_install();
void isr_handler(regs_t *r);

//isr handler functions
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();



