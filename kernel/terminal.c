// terminal.c - defines basic functions for a terminal driver
// Ben Staehle - 8/26/25

#include <stdbool.h>

#include "terminal.h"
#include "video.h"

// current colors
static color_t curr_fg;
static color_t curr_bg;

// current position
static term_pos_t curr_pos;

// cursor settings
static bool show_cursor = true;

int TERM_ROWS;
int TERM_COLS;

void term_clear() {
    //clear the screen to the bg color
    clear_scr(curr_bg);
    
    curr_pos.x = 0;
    curr_pos.y = 0;
}

void term_clear_color(color_t c) {
    //clear the screen to the bg color
    clear_scr(c);
    
    curr_pos.x = 0;
    curr_pos.y = 0;

}

void term_init(color_t fg, color_t bg) {
    curr_fg = fg;
    curr_bg = bg;

    term_clear();

    // calculate the number of rows and cols
    TERM_ROWS = HEIGHT / GLYPH_H;
    TERM_COLS = WIDTH / GLYPH_W;
}

void term_putc(char c) {
    if (c == '\n') {
        term_scroll();
    } else {
        draw_char(
            curr_pos.x * GLYPH_W,
            curr_pos.y * GLYPH_H,
            curr_fg,
            curr_bg,
            c
        );
        
        // increment current position
        curr_pos.x++; 
    }

    // draw the cursor (but do not increment term_pos)
    if (show_cursor) {
        draw_char(
        curr_pos.x * GLYPH_W,
        curr_pos.y * GLYPH_H,
       curr_fg,
       curr_bg,
           '\0'
        ); 
    }
}

void term_puts(char *str) {
    while(*str != '\0') {
        term_putc(*str);
        ++str;
    }
}

void term_scroll() {
    // check if we need to scroll the whole screen
    if ((curr_pos.y + 1) > TERM_ROWS) {
        //TODO implement this
        curr_pos.x = 0;
        curr_pos.y = 0;

    } else {
        // just reset the cursor
        curr_pos.y++;
        curr_pos.x = 0;
    }
}

void term_enable_cursor(void) {
    show_cursor = true;
}

void term_disable_cursor(void) {
    show_cursor = false;
}

void term_set_fg(color_t c) {
    curr_fg = c;
}

void term_set_bg(color_t c) {
    curr_bg = c;
}
