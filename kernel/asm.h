// asm.h - defines various asm functions
// Ben Staehle - 8/19/25
#pragma once

static void sti() {
   asm volatile ("sti");
}
