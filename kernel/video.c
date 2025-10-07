// video.c - defines a basic kernel video driver
// Ben Staehle - 8/18/25
#include "multiboot2.h"
#include "video.h"

uint32_t *framebuf;

void putpixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!fb_tag) return;
    if (fb_tag->framebuffer_type != 1 || fb_tag->bpp != 32) return; // RGB32 only

    uint8_t* fb = (uint8_t*)(uintptr_t)fb_tag->framebuffer_addr;
    uint32_t* pixel = (uint32_t*)(fb + y * fb_tag->framebuffer_pitch + x * (fb_tag->bpp / 8));

    *pixel = color;
}

void clear_scr(uint32_t color) {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            putpixel(x, y, color);
        }
    }
}

void kvideo_init() {
    // save the framebuffer address
    framebuf = (uint32_t*)fb_tag->framebuffer_addr;

    //clear the screen to black
    clear_scr(BLACK);
}

uint8_t font_bitmap_index(char c) {
    if (c >= '0' && c <= '9') return (uint8_t)(1 + (c - '0'));            // 1..10
    if (c >= 'A' && c <= 'Z') return (uint8_t)(11 + (c - 'A'));           // 11..36
    switch (c) {
        case ' ': return 37;
        case '.': return 38;
        case ',': return 39;
        case ':': return 40;
        case ';': return 41;
        case '!': return 42;
        case '?': return 43;
        case '-': return 44;
        case '+': return 45;
        case '=': return 46;
        case '/': return 47;
        case '(': return 48;
        case ')': return 49;
        case '[': return 50;
        case ']': return 51;
        case '<': return 52;
        case '>': return 53;
        case '%': return 54;
        default:  return 0;  // fallback box ▯
    }
}

#define FONT_BITMAP_COUNT (sizeof(FONT_BITMAP) / sizeof(FONT_BITMAP[0]))

void draw_glyph(int x, int y, uint32_t fg, uint32_t bg, const uint8_t glyph[8]) {
    uint8_t bits;
    uint8_t mask;

    for (int row = 0; row < GLYPH_H; ++row) {
        bits = glyph[row];
        mask = 0x80;
        for (int col = 0; col < GLYPH_W; ++col) {
            if (bits & mask) {
                putpixel(x + col, y + row, fg);               
            } else {
                putpixel(x + col, y + row, bg);
            }

            mask >>= 1;
        }
    }
}

void draw_char(int x, int y, uint32_t fg, uint32_t bg, char c) {
    uint8_t idx = font_bitmap_index(c);
    if (idx >= FONT_BITMAP_COUNT) {
        idx = 0; // fallback box
    }
    draw_glyph(x, y, fg, bg, FONT_BITMAP[idx]);
}

void draw_str(int x, int y, uint32_t fg, uint32_t bg, const char* s) {
    char *ptr = (char*)s;
    int char_x = x;

    while (*ptr != '\0') {
        draw_char(char_x, y, fg, bg, *ptr);        
        char_x += GLYPH_W;
        ptr++;
    }
}


