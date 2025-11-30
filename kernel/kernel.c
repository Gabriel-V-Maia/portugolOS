#include <stdint.h>
#include "keyboard/keyboard.h"
#include "libs/kprintf.h"
#include "multiboot.h"  

void kernel_main(uint32_t magic, multiboot_info_t* mbi) {
    kclear();
    kprintf("Bem vindo ao portugol OS!!\n\n");
    
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("ERRO: Nao foi bootado pelo GRUB!\n");
        kprintf("Magic recebido: 0x%x\n", magic);
        for(;;);
    }
    
    kprintf("GRUB detectado! Magic: 0x%x\n", magic);
    
    if (mbi->flags & MULTIBOOT_INFO_MEMORY) {
        uint32_t mem_lower_kb = mbi->mem_lower;
        uint32_t mem_upper_kb = mbi->mem_upper;
        uint32_t total_mb = (mem_lower_kb + mem_upper_kb) / 1024;
        
        kprintf("Memoria detectada: %d MB\n", total_mb);
        kprintf("  - Lower: %d KB\n", mem_lower_kb);
        kprintf("  - Upper: %d KB\n", mem_upper_kb);
    }
    
    if (mbi->flags & MULTIBOOT_INFO_MEM_MAP) {
        kprintf("\nMemory Map:\n");
        
        multiboot_mmap_entry_t* mmap = (multiboot_mmap_entry_t*)mbi->mmap_addr;
        multiboot_mmap_entry_t* mmap_end = (multiboot_mmap_entry_t*)(mbi->mmap_addr + mbi->mmap_length);
        
        int region = 0;
        while (mmap < mmap_end) {
            kprintf("  Regiao %d: 0x%x - 0x%x (%s)\n",
                    region++,
                    (uint32_t)mmap->addr,
                    (uint32_t)(mmap->addr + mmap->len),
                    mmap->type == 1 ? "USAVEL" : "RESERVADO");
            
            mmap = (multiboot_mmap_entry_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
        }
    }
    
    kprintf("\n\n");
    
    while (1) {   
        char input = keyboard_read();
        if (input != 0) {
            char str[2] = {input, '\0'};
            kprintf(str);
        }
    }
}

