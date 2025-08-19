// video.c - defines a basic kernel video driver
// Ben Staehle - 8/18/25
#include "multiboot2.h"

void putpixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!fb_tag) return;
    if (fb_tag->framebuffer_type != 1 || fb_tag->bpp != 32) return; // RGB32 only

    uint32_t* pixel = (uint32_t*)(fb_tag->framebuffer_addr + y * fb_tag->framebuffer_pitch + x * 4);
    *pixel = color;
}

void draw_test() {
    if (!fb_tag) return;

    for (uint32_t y = 0; y < fb_tag->height; y++) {
        for (uint32_t x = 0; x < fb_tag->width; x++) {
            putpixel(x, y, 0xFF0000FF); // Blue
        }
    }
}
