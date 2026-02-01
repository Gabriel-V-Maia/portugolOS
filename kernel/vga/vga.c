#include <stdint.h>
#include "vga.h"

static uint16_t* vga_buffer = (uint16_t*)0xB8000;
static int row = 0, col = 0;

static inline uint8_t color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

static void vga_scroll() {
    for (int i = 0; i < 80 * 24; i++) {
        vga_buffer[i] = vga_buffer[i + 80];
    }
    
    for (int i = 80 * 24; i < 80 * 25; i++) {
        vga_buffer[i] = (uint16_t)' ' | (15 << 8);
    }
    
    row = 24;
    col = 0;
}

void vga_putc(char c) {
    if (c == '\n') {
        row++;
        col = 0;
        
        if (row >= 25) {
            vga_scroll();
        }
        return;
    }
    
    if (c == '\b') {  
        if (col > 0) {
            col--;
            vga_buffer[row * 80 + col] = (uint16_t)' ' | (15 << 8);
        }
        return;
    }
    
    uint16_t val = (uint16_t)c | (uint16_t)color(15, 0) << 8;
    vga_buffer[row * 80 + col] = val;
    col++;
    
    if (col >= 80) {
        col = 0;
        row++;
        
        if (row >= 25) {
            vga_scroll();
        }
    }
}

void vga_print(const char* s) {
    while (*s) vga_putc(*s++);
}

void vga_clear() {
    for (int i = 0; i < 80 * 25; i++)
        vga_buffer[i] = (uint16_t)' ' | (15 << 8);
    row = col = 0;
}
