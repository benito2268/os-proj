// panic.c - kernel panic code
// Ben Staehle - 8/31/25

#include "utils.h"
#include "terminal.h"

__attribute__((noreturn))
void panic(char *msg) {
    // get the cpu registers
    

    // print the messages
    // and emulate the classic blue screen ;)
    term_clear_color(BLUE);
    term_set_bg(BLUE);

    kprintf("\nKERNEL: (PANIC) A FATAL SYSTEM ERROR HAS OCCURRED!\n");
    kprintf("\n    %s\n\n", msg);
    kprintf("\nBELOW IS A CRASH DUMP CONTAINING INFORMATION\nABOUT THE SYSTEM WHEN THE ERROR OCCURRED\n");

    kprintf("\n\nPLEASE REBOOT THE MACHINE...");


    // spin forever (or until the system reboots)
    for (;;) {
        cpu_relax();
    }
}

void cpu_relax() {
    asm volatile ("nop");
}
