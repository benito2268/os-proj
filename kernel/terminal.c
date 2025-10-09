// terminal.c - defines basic functions for a terminal driver
// Ben Staehle - 8/26/25

#include <stdbool.h>
#include <string.h>

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
        // erase the cursor mark at the end of the line
        if (show_cursor) {
             draw_char(
            curr_pos.x * GLYPH_W,
            curr_pos.y * GLYPH_H,
           curr_fg,
           curr_bg,
               ' '
            );   
        }

        term_scroll();
    } else if (c == '\b') {
        // backspace
        term_backspace();

        // term_bs handles the cursor
        return;
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
        draw_charW(
        curr_pos.x * GLYPH_W,
        curr_pos.y * GLYPH_H,
       curr_fg,
       curr_bg,
           L'█'
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
    if (curr_pos.y >= TERM_ROWS - 1) {
        uint32_t *term_begin = get_framebuf_addr();
        int px_per_scanline = GLYPH_W * TERM_COLS;

        memmove(term_begin,
                term_begin + (px_per_scanline * GLYPH_H),
                px_per_scanline * GLYPH_H * (TERM_ROWS - 1) * sizeof(uint32_t));

        // Clear the bottom row here
        uint32_t *bottom = term_begin + (px_per_scanline * GLYPH_H * (TERM_ROWS - 1));
        memset(bottom, 0, px_per_scanline * GLYPH_H * sizeof(uint32_t));

        // set the terminal pos
        curr_pos.x = 0;
        curr_pos.y = TERM_ROWS - 1;

    } else {
        // just reset the cursor
        curr_pos.y++;
        curr_pos.x = 0;
    }
}

void term_backspace() {
    // just erase the previous char and set the position back one
    if (curr_pos.x == 0) {
        // at the beginning of the line
        // currently you can't erase previous lines
        // TODO revisit this when I make the real terminal driver (stream based)
        return;
    }

    // decrement pos.x and draw a space (or cursor)
    if (show_cursor) {
        // clear the cursor space, and redraw the cursor
        draw_char(
        curr_pos.x * GLYPH_W,
        curr_pos.y * GLYPH_H,
       curr_fg,
       curr_bg,
           ' '
        ); 
        curr_pos.x--;
        draw_charW(
        curr_pos.x * GLYPH_W,
        curr_pos.y * GLYPH_H,
       curr_fg,
       curr_bg,
           L'█'
        );

    } else {
        curr_pos.x--;
        draw_char(
        curr_pos.x * GLYPH_W,
        curr_pos.y * GLYPH_H,
       curr_fg,
       curr_bg,
           ' '
        ); 
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
