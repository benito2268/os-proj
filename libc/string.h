// string.h - part of the c standard library
// Ben Staehle - 8/28/25
#pragma once

#include <stddef.h>

#define __IS_LIBK

// libk only functions
#ifdef __IS_LIBK
char *kstrrev(char *s);


#endif

// libc only functions
#ifdef __IS_LIBC


#endif

//shared functions
void *memset(void *s, int c, size_t n);
void *memmove(void *d, const void* s, size_t n);
size_t strlen(const char *s);
