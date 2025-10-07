// kprintf.c - defines the kernel printf function
// Ben Staehle - 8/26/25

#include <stdint.h>
#include <stdarg.h>
#include "stdio.h"
#include "string.h"

// kernel file includes
#include "../kernel/terminal.h"

#define NUM_BUF_SIZE 512

//TODO move to stdlib.c
//NOTE: does not support negetive base 10 numbers yet
static char *itoa(uint32_t value, char *str, int base) {
    int curr_pos = 0; 

    if (base < 2 || base > 32) {
        str[0] = '\0';
        return str;
    }

    // handle 0 explicitly
    if (value == 0) {
        str[curr_pos] = '0';
        return str;
    }

    // do the conversion
    while (value) {
        int digit = value % base;
        value /= base;

        // convert to ascii and save
        if (digit < 10) {
            str[curr_pos++] = '0' + digit;   
        } else {
            str[curr_pos++] = 'A' + (digit - 10);
        }
    }

    str[curr_pos] = '\0';

    // reverse the string
    str = kstrrev(str);

    return str;
}

//TODO move to stdlib.c
static int atoi(char *s) {
    int result = 0;
    int sign = 1;  

    // handle negatives
    if (*s == '-') {
        sign = -sign;
        ++s;
    }

    // do the conversion
    while (*s) {
        result = result * 10 + (*s - '0'); 
        ++s;
    }

    return result * sign;
}

//TODO move to ctype.c
static int isdigit(char c) {
    return c > '0' && c < '9';
}

// NOTE: this function does not support all standard specifiers
// currently it supports:
// - %d for ints
// - %s for strings
// - %x for hexadecimal ints
int kprintf(const char * restrict fmt, ...) {
    va_list va;
    va_start(va, fmt);

    int left_pad = 0;
    char itoa_buf[NUM_BUF_SIZE] = { '\0' };

    while(*fmt != '\0') {
         if (*fmt == '%') {
            //increment and see which specifier
            ++fmt;

            // check for padding specifiers
            char buf[NUM_BUF_SIZE] = { '\0' };
            int buf_idx = 0;
            while (isdigit(*fmt)) {
                buf[buf_idx++] = *fmt; 
                ++fmt;
            }

            //convert to an int
            if (*buf) {
                left_pad = atoi(buf);
            }

            switch (*fmt) {
                case 'd':
                    int num = va_arg(va, int);

                    itoa(num, itoa_buf, 10);
                    
                    // do any left padding
                    int final_pad = left_pad - strlen(itoa_buf);
                        while (final_pad > 0) {
                        term_putc('0'); 
                        --final_pad;
                    }

                    term_puts(itoa_buf);
                    
                    break;
                case 'x':
                    // very similar to %d
                    term_puts("0X");
                    num = va_arg(va, int);
                
                    itoa(num, itoa_buf, 16);
                    
                     // do any left padding
                    final_pad = left_pad - strlen(itoa_buf);
                    while (final_pad > 0) {
                        term_putc('0'); 
                        --final_pad;
                    }

                    term_puts(itoa_buf);

                    break;
                case 's':
                    char *s = va_arg(va, char*);
                    term_puts(s);

                    break;
                case '%':
                    // escape '%'
                    term_putc('%');
                    
                    break;
                default:
                    // unknown specifier
                    break;
            }

            // zero out the left pad for the next thing
            left_pad = 0;

        } else {
            // print the char normally
            // or handle an escape sequence
            if (*fmt == '\\') {
                switch (*(++fmt)) {
                    case 'n':
                        term_putc('\n');
                        break;
                    case 't':
                        term_puts("    ");
                        break;
                    case 'r':
                        term_putc('\n');
                        break;
                }
            }

            term_putc(*fmt);
        }

        ++fmt;
    }

    va_end(va);
    return 0;
}
