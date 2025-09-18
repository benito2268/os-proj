// panic.c - kernel panic code
// Ben Staehle - 8/31/25

#include <stdio.h>

#include "utils.h"
#include "terminal.h"

__attribute__((noreturn))
void panic(char *msg, bool is_trap, trap_frame_t *f) {
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
    kprintf("\n\n    EAX=%8x EBX=%8x ECX=%8x EDX=%8x\n", r.eax, r.ebx, r.ecx, r.edx);
    kprintf("    ESP=%8x EBP=%8x ESI=%8x EDI=%8x\n", esp, ebp, r.esi, r.edi);
    kprintf("    CR0=%8x CR2=%8x CR3=%8x\n", r.cr0, r.cr2, r.cr3);
    kprintf("    EFLAGS=%8x\n", r.eflags);

    kprintf("\n\nPLEASE REBOOT THE MACHINE...");


    // spin forever (or until the system reboots)
    for (;;) {
        cpu_relax();
    }
}

void cpu_relax() {
    asm volatile ("nop");
}
