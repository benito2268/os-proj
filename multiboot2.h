// multiboot2.h - defines multiboot struct and parsing functions
// Ben Staehle - 8/18/25
#pragma once

#include <stdint.h>

typedef struct __mb2_tag__ {
	uint32_t type;
	uint32_t size;

} mb2_tag_t;

typedef struct __mb2_fb_tag__ {
    uint32_t type;
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
    uint8_t framebuffer_type;
    uint16_t reserved;
} mb2_fb_tag_t;

extern mb2_fb_tag_t *fb_tag;

void parse_mb2_header(uint32_t addr);
