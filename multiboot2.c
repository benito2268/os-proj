// multiboot2.c - defines multiboot struct and parsing functions
// Ben Staehle - 8/18/25

#include "multiboot2.h"

mb2_fb_tag_t* fb_tag = 0;

void parse_mb2_header(uint32_t addr) {
    uint32_t total_size = *(uint32_t*)addr;
    uint32_t reserved   = *((uint32_t*)addr + 1);

    uint8_t* ptr = (uint8_t*)addr + 8;

    while (ptr < (uint8_t*)addr + total_size) {
        mb2_tag_t* tag = (mb2_tag_t*)ptr;

        if (tag->type == 0) break;  // End tag
        if (tag->type == 8) {        // Framebuffer tag
            fb_tag = (mb2_fb_tag_t*)tag;
        }

        // Align to 8 bytes
        ptr += ((tag->size + 7) & ~7);
    }
}

