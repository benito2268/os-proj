// isr.h - defines inturrupt service routines 0-31
// Ben Staehle - 8/19/25
#pragma once

#include <stdint.h>

#define N_ISRS 32

static const char *isr_msgs[32] = {
   "DIVIDE BY ZERO",
   "DEBUG EXCEPTION",
   "NMI",
   "BREAKPOINT",
   "OVERFLOW",
   "BOUND RANGE EXCEEDED",
   "INVLIAD OPCODE",
   "DEVICE NOT AVAILABLE",
   "DOUBLE FAULT",
   "COPROCESSOR SEGMENT OVERRUN",
   "INVALID TSS",
   "SEGMENT NOT PRESENT",
   "STACK SEGMENT FAULT",
   "GENERAL PROTECTION FAULT",
   "PAGE FAULT",
   "RESERVED",
   "X87 FLOATING POINT ERROR",
   "ALIGNMENT CHECK",
   "MACHINE CHECK",
   "SIMD FLOATING POINT EXCEPTION",
   "VIRTUALIZATION EXCEPTION",
   "CONTROL PROTECTION EXCEPTION",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
   "RESERVED",
};

typedef struct __trap_frame__ {
    // GP registers
    uint32_t edi, esi, ebp, old_esp;
    uint32_t ebx, edx, ecx, eax;

    // segment regs
    uint32_t gs, fs, es, ds;

    uint32_t trap_no;

    // values pushed by the hardware
    uint32_t err_code, eip, cs, eflags;

    // values pushed by hardware during a PL change
    uint32_t esp, ss;

} trap_frame_t;

void isr_install();
void trap(trap_frame_t *r);

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

static void (*isr_vecs[N_ISRS])(void) = {
    isr0,
    isr1,
    isr2,
    isr3,
    isr4,
    isr5,
    isr6,
    isr7,
    isr8,
    isr9,
    isr10,
    isr11,
    isr12,
    isr13,
    isr14,
    isr15,
    isr16,
    isr17,
    isr18,
    isr19,
    isr20,
    isr21,
    isr22,
    isr23,
    isr24,
    isr25,
    isr26,
    isr27,
    isr28,
    isr29,
    isr30,
    isr31,
};

