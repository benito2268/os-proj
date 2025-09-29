// isr.c - defines inturrupt handler functions
// Ben Staehle - 9/3/25
#include "isr.h"
#include "utils.h"
#include "irq.h"

void trap(trap_frame_t *r) {
    // panic on exception
    if (r->trap_no < 32) {
        panic(isr_msgs[r->trap_no], true, r);
        // this does not return
    } else if (r->trap_no > 47) {
        panic("ILLEGAL TRAP/IRQ", true, r);
        // this does not return
    }

    // otherwise handle the IRQ
    IRQ_VECS[r->trap_no - 32]();

    IRQ_issue_EOI(r->trap_no);
}
