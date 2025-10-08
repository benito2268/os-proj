// keyboard.h - defines a basic kernel keyboard driver to echo chars
// Ben Staehle - 10/7/25
#pragma once

#include "types.h"

#define PS2_DATA   0x60
#define PS2_STATUS 0x64  // when read from
#define PS2_CMD    0x64  // when written to

#define KB_IRQ_NUM 0x01

#define KEY_RELEASE 0x80

#define IS_KEY_PRESS(sc) (!((sc) & KEY_RELEASE))
#define IS_KEY_RELEASE(sc) ((sc) & KEY_RELEASE)

// scancode mappings
static const char sc2char[128] = {
    0,    // 0x00
    27,   // 0x01 ESC
    '1',  // 0x02
    '2',  // 0x03
    '3',  // 0x04
    '4',  // 0x05
    '5',  // 0x06
    '6',  // 0x07
    '7',  // 0x08
    '8',  // 0x09
    '9',  // 0x0A
    '0',  // 0x0B
    '-',  // 0x0C
    '=',  // 0x0D
    '\b', // 0x0E Backspace
    '\t', // 0x0F Tab
    'q',  // 0x10
    'w',  // 0x11
    'e',  // 0x12
    'r',  // 0x13
    't',  // 0x14
    'y',  // 0x15
    'u',  // 0x16
    'i',  // 0x17
    'o',  // 0x18
    'p',  // 0x19
    '[',  // 0x1A
    ']',  // 0x1B
    '\n', // 0x1C Enter
    0,    // 0x1D Ctrl
    'a',  // 0x1E
    's',  // 0x1F
    'd',  // 0x20
    'f',  // 0x21
    'g',  // 0x22
    'h',  // 0x23
    'j',  // 0x24
    'k',  // 0x25
    'l',  // 0x26
    ';',  // 0x27
    '\'', // 0x28
    '`',  // 0x29
    0,    // 0x2A Left Shift
    '\\', // 0x2B
    'z',  // 0x2C
    'x',  // 0x2D
    'c',  // 0x2E
    'v',  // 0x2F
    'b',  // 0x30
    'n',  // 0x31
    'm',  // 0x32
    ',',  // 0x33
    '.',  // 0x34
    '/',  // 0x35
    0,    // 0x36 Right Shift
    '*',  // 0x37 Keypad *
    0,    // 0x38 Alt
    ' ',  // 0x39 Space
    0,    // 0x3A Caps Lock
    // ... fill in other keys as needed
};

void kb_init(void);
void kb_handle_irq(void);
void kb_echo_key(char c);
