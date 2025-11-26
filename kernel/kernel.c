#include <stdint.h>
#include "keyboard/keyboard.h"
#include "vga/vga.h"

void vga_print(const char*);
void vga_clear();
char keyboard_read();

void kernel_main() {
    vga_clear();
    vga_print("Bem vindo ao Portugol OS!!\n");
    vga_print("> ");

    char buffer[128];
    int idx = 0;

    while(1) {
        char c = keyboard_read();
        if(!c) continue;

        if(c == '\n') {
            buffer[idx] = 0;

            if(!__builtin_strcmp(buffer, "help"))
                vga_print("\nCommands: help, clear\n");
            else if(!__builtin_strcmp(buffer, "clear")) {
                vga_clear();
                vga_print("> ");
            } else {
                vga_print("\nUnknown command\n");
            }

            idx = 0;
            vga_print("> ");
        } else {
            buffer[idx++] = c;
            vga_putc(c);
        }
    }
}

