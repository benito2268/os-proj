// string.c - hold c std lib string functions
// Ben Staehle - 8/31/25
#include <stddef.h>

#include "string.h"

size_t strlen(const char *s) {
    size_t cnt = 0;
    while (*s) {
        ++cnt;
        ++s;
    }

    return cnt;
}

char *kstrrev(char *s) {
    int left = 0;
    int right = strlen(s) - 1;
    char temp;

    while (left < right) {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        ++left;
        --right;
    }

    return s;
}

void *memset(void *s, int c, size_t n) {
    if (!s) {
        return NULL; // invlaid memory
    }

    int *ptr = (int*)s;
    for (size_t i = 0; i < n; ++i) {
        ptr[i] = c; 
    }

    return s;
}

void *memmove(void *d, const void* s, size_t n) {
    char *cdest = (char*)d;
    char *csrc = (char*)s;

    if (!s || !d) { 
        return NULL; // invalid memory
    }

    if (d <= s) {
        while(n--) {
            *cdest++ = *csrc++;
        }
    }
    else if (d > s) {
        cdest += n - 1;
        csrc += n - 1;
        while(n--) {
            *cdest-- = *csrc--;
        }
    }

    return d;
}
