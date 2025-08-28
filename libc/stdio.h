// stdio.h - part of the C standard library
// Ben Staehle - 8/26/25
#pragma once

//TODO address with compiler flags
#define _IS_LIBK

#ifdef _IS_LIBK

int kprintf(const char * restrict fmt, ...);

#endif

#ifdef _IS_LIBC

int printf(const char * restrict fmt, ...);

#endif
