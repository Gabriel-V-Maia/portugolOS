#include "keyboard/keyboard.h"
#include "libs/kprintf.h"
#include "multiboot.h"  
#include "checks/bootloader_magic.h"
#include "libs/string.h"
#include "mm/memory.h"

#define CMD_BUFFER_SIZE 256

static char cmd_buffer[CMD_BUFFER_SIZE];
static int cmd_index = 0;

void kernel_main(unsigned int magic, multiboot_info_t* mbi) {
    kclear();
    mem_init(mbi->mem_lower, mbi->mem_upper);
    kprintf("Bem vindo ao portugol OS!!\n\n");

    check_grub(magic);

    kprintf("portugolOS> ");


    for(;;) {   
        char input = keyboard_read();
        
        if (input != 0) {
            if (input == '\n') {
                cmd_buffer[cmd_index] = '\0'; 
                kprintf("\n");
                
                process_command(cmd_buffer);
                
                cmd_index = 0;
                cmd_buffer[0] = '\0';
                
                kprintf("portugolOS> ");
            }
            else if (input == '\b') {
                if (cmd_index > 0) {
                    cmd_index--;
                    cmd_buffer[cmd_index] = '\0';
                    kprintf("\b \b");
                }
            }
            else {
                if (cmd_index < CMD_BUFFER_SIZE - 1) {
                    cmd_buffer[cmd_index++] = input;
                    char str[2] = {input, '\0'};
                    kprintf(str);
                }
            }
        }
    }
}

