// asm.h - defines various asm functions

// Ben Staehle - 8/19/25
#pragma once

#include <stdint.h>
#include "types.h"

// asm defines
#define NO_GCC_OPTIM asm volatile ("pause")

// asm functions

static void sti() {
    asm volatile ("sti");
}

static void cli() {
    asm volatile ("cli");
}

static ubyte inb(ushort port) {
    ubyte ret; 
    asm volatile ("in %1,%0" : "=a" (ret) : "d" (port));
    return ret;
}

static void outb(ushort port, ubyte data) {
    asm volatile ("out %0,%1" :: "a" (data), "d" (port));
}

static void io_wait() {
    outb(0x80, 0);
}
