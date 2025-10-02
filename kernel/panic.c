// panic.c - kernel panic code
// Ben Staehle - 8/31/25

#include <stdio.h>

#include "utils.h"
#include "terminal.h"

#define STACK_DUMP_LEN 32

static void dump_stack(uint32_t *esp) {
    kprintf("\n\n    STACK DUMP FROM %8x:\n", esp);
    kprintf("    ============================================================");
    for (int i = 0; i < STACK_DUMP_LEN; ++i) {
        if (i % 4 == 0) {
            kprintf("\n    %8x: ", (uint32_t)(esp + i));
        }
        kprintf("%8x ", esp[i]);
    }
    kprintf("\n    ===========================================================");
}

static void kbacktrace(uint32_t ebp) {

}

__attribute__((noreturn))
void panic(const char *msg, bool is_trap, trap_frame_t *f) {
    // location sensitive regs
    uint32_t eip, esp, ebp;

    // get the cpu registers
    regs_t r;
    dump_regs(&r); 

    if (is_trap) {
        eip = f->eip;
        esp = f->esp;
        ebp = f->ebp;
    } else {
        eip = r.eip;
        esp = r.esp;
        ebp = r.ebp;
    }

    // print the messages
    // and emulate the classic blue screen ;)
    term_clear_color(BLUE);
    term_set_bg(BLUE);

    kprintf("\nKERNEL: (PANIC) A FATAL SYSTEM ERROR HAS OCCURRED!\n");
    kprintf("\n    %s AT EIP=%8x\n\n", msg, eip);
    kprintf("\nBELOW IS A CRASH DUMP CONTAINING INFORMATION\nABOUT THE SYSTEM WHEN THE ERROR OCCURRED\n");

    // print the crash dump
    kprintf("\n\n    PROCESSOR REGISTERS:\n");
    kprintf("    ===========================================================\n");
    kprintf("    EAX=%8x EBX=%8x ECX=%8x EDX=%8x\n", r.eax, r.ebx, r.ecx, r.edx);
    kprintf("    ESP=%8x EBP=%8x ESI=%8x EDI=%8x\n", esp, ebp, r.esi, r.edi);
    kprintf("    CR0=%8x CR2=%8x CR3=%8x\n", r.cr0, r.cr2, r.cr3);
    kprintf("    EFLAGS=%8x\n", r.eflags);
    kprintf("    ===========================================================\n");

    // dump the stack and print a back trace
    dump_stack((uint32_t*)f->esp);
    kbacktrace(f->ebp);

    kprintf("\n\nPLEASE REBOOT THE MACHINE...");


    // spin forever (or until the system reboots)
    for (;;) {
        cpu_relax();
    }
}

void cpu_relax() {
    asm volatile ("nop");
}
