// asm.h - defines various asm functions
// Ben Staehle - 8/19/25
#pragma once

#include <stdint.h>

#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

static void sti() {
   asm volatile ("sti");
}

static uint8_t inb(uint8_t port) {
   asm volatile ("");
   return 0x0;
}

static void outb(uint16_t port, uint8_t data) {
   asm volatile ("out %0,%1" :: "a" (data), "d" (port));
}
