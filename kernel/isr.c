// isr.c - defines inturrupt handler functions
// Ben Staehle - 9/3/25
#include <stddef.h>

#include "isr.h"
#include "utils.h"
#include "irq.h"
#include "types.h"

void trap(trap_frame_t *r) {
    ubyte irq_no = r->trap_no - 32; // only used if it's an IRQ

    // panic on exception
    if (r->trap_no < 32) {
        panic(isr_msgs[r->trap_no], true, r);
        // this does not return
    } else if (r->trap_no > 47) {
        panic("ILLEGAL TRAP/IRQ", true, r);
        // this does not return
    }

    // otherwise handle the IRQ
    if (IRQ_VECS[irq_no] != NULL) {
        IRQ_VECS[irq_no]();
    }
        
    IRQ_issue_EOI(irq_no);
}
