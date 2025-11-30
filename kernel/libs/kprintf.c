#include "kprintf.h"
#include "../vga/vga.h"
#include <stdarg.h>
#include <stdint.h>

static void itoa(int num, char *str, int base) {
    int i = 0;
    int isNegative = 0;
    
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }
    
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num = num / base;
    }
    
    if (isNegative)
        str[i++] = '-';
    
    str[i] = '\0';
    
    // Inverte
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void kprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buf[32];
    
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
                case 'd':  // Inteiro
                    itoa(va_arg(args, int), buf, 10);
                    vga_print(buf);
                    break;
                    
                case 'x':  // Hex
                    itoa(va_arg(args, int), buf, 16);
                    vga_print(buf);
                    break;
                    
                case 's':  // String
                    vga_print(va_arg(args, char*));
                    break;
                    
                case 'c':  // Char
                    buf[0] = va_arg(args, int);
                    buf[1] = '\0';
                    vga_print(buf);
                    break;
                    
                default:
                    buf[0] = format[i];
                    buf[1] = '\0';
                    vga_print(buf);
            }
        } else {
            buf[0] = format[i];
            buf[1] = '\0';
            vga_print(buf);
        }
    }
    
    va_end(args);
}

void kclear(void) {
    vga_clear();
}

