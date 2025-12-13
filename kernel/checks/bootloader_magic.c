#include <stdint.h>
#include "../libs/kprintf.h"
#include "../multiboot.h"  
#include "bootloader_magic.h"

void check_grub(uint32_t magic)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("ERRO: Nao foi bootado pelo GRUB!\n");
        kprintf("Magic recebido: 0x%x\n", magic);
        for (;;);
    }
}
