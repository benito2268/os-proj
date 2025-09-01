// string.c - hold c std lib string functions
// Ben Staehle - 8/31/25
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
    int *ptr = (int*)s;
    for (size_t i = 0; i < n; ++i) {
        ptr[i] = c; 
    }

    return s;
}
