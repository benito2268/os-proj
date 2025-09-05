// isr.c - defines inturrupt handler functions
// Ben Staehle - 9/3/25
#include "isr.h"
#include "utils.h"

void isr_install() {

}

void trap(trap_frame_t *r) {
    // panic on exception
    if (r->trap_no < 32) {
        panic(isr_msgs[r->trap_no]);
    }

    //TODO otherwise handle the interrupt
}
