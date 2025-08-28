// kprintf.c - defines the kernel printf function
// Ben Staehle - 8/26/25

#include <stdarg.h>
#include "stdio.h"

// kernel file includes
#include "../kernel/terminal.h"

#define NUM_BUF_SIZE 512

static char *itoa(int value, char *str, int base) {
    int curr_pos = 0;

    if (base < 2 || base > 32) {
        str[0] = '\0';
        return str;
    }

    //put '0x' or '0b' for base 16 and 2
    if (base == 16) {
        str[0] = '0';
        str[1] = 'x';
        curr_pos = 2;

    } else if (base == 2) {
        str[0] = '0';
        str[1] = 'b';
        curr_pos = 2;
    }

    //handle 0 explicitly
    if (value == 0) {
        str[curr_pos] = '0';
        return str;
    }
}

// NOTE: this function does not support all standard specifiers
// currently it supports:
// - %d for ints
// - %s for strings
// - %x for hexadecimal ints
int kprintf(const char * restrict fmt, ...) {
    va_list va;
    va_start(va, fmt);

    while(*fmt != '\0') {
        if (*fmt == '%') {
            //increment and see which specifier
            ++fmt;
            switch (*fmt) {
                case 'd':
                    int num = va_arg(va, int);

                    //TODO need a more complex system here
                    term_putc((char)(num + 0x30));
                    
                    break;
                case 'x':
                    break;
                case 's':
                    char *s = va_arg(va, char*);
                    term_puts(s);

                    break;
                default:
                    // unknown specifier
                    break;
            }

        } else {
            // print the char normally
            term_putc(*fmt);
        }

        ++fmt;
    }

    va_end(va);
    return 0;
}
