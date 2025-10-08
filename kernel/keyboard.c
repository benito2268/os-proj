// keyboard.c - defines a basic kernel keyboard driver to echo chars
// Ben Staehle - 10/7/25
#include "keyboard.h"
#include "irq.h"
#include "asm.h"
#include "utils.h"
#include "terminal.h"

void kb_init(void) {
    // install the keyboard handler on IRQ 1
    IRQ_install(KB_IRQ_NUM, kb_handle_irq);                               
}

void kb_handle_irq(void) {
    // disable IRQs while this one is handled
    // TODO probably make this function reentrant
    // and leave interrupts on
    cli();

    // read the scancode
    ushort scancode = (ushort)inb(PS2_DATA);

    // translate the scancode into a char
    if (IS_KEY_PRESS(scancode)) {
        char c = sc2char[scancode & 0x7F];
   
        // do a little funny since only uppercase supported
        if (c >= 'a' && c <= 'z') {
            c -= 32; // convert to uppercase
        }

        // echo to the screen
        term_putc(c);
    }

    sti();
}

 
