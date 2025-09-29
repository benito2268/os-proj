// asm.h - defines various asm functions

// Ben Staehle - 8/19/25
#pragma once

#include <stdint.h>

// asm defines
#define EMPTY_LOOP asm volatile ("pause")


// asm functions

static void sti() {
   asm volatile ("sti");
}

static void cli() {
   asm volatile ("cli");
}

static uint8_t inb(uint8_t port) {
   asm volatile ("");
   return 0x0;
}

static void outb(uint16_t port, uint8_t data) {
   asm volatile ("out %0,%1" :: "a" (data), "d" (port));
}

static void io_wait() {
   outb(0x80, 0);
}