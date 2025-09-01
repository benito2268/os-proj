// terminal.h - defines basic functions for a terminal driver
// Ben Staehle - 8/26/25
#pragma once

#include <stdint.h>
#include "video_defs.h"

typedef uint32_t color_t;

typedef struct __term_pos__ {
    uint32_t x;
    uint32_t y;

} term_pos_t;

extern int TERM_ROWS;
extern int TERM_COLS;

void term_init(color_t fg, color_t bg);
void term_clear();
void term_clear_color(color_t c);

void term_putc(char c);
void term_puts(char *str);
void term_scroll();

void term_set_fg(color_t c);
void term_set_bg(color_t c);
