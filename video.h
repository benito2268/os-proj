// video.h - defines a basic kernel video driver
// Ben Staehle - 8/18/25
#pragma once

#include <stdint.h>

void putpixel(uint32_t x, uint32_t y, uint32_t color);
void draw_test();
