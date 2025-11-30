#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

// Número mágico que o GRUB passa
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

// Flags do multiboot info
#define MULTIBOOT_INFO_MEMORY     0x00000001
#define MULTIBOOT_INFO_MEM_MAP    0x00000040

// Estrutura que o GRUB passa pro kernel
typedef struct multiboot_info {
    uint32_t flags;           // Quais campos são válidos
    uint32_t mem_lower;       // KB de memória abaixo de 1MB
    uint32_t mem_upper;       // KB de memória acima de 1MB
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;     // Tamanho do memory map
    uint32_t mmap_addr;       // ENDEREÇO do memory map
    // ... outros campos que não vamos usar agora
} __attribute__((packed)) multiboot_info_t;

// Entrada do memory map
typedef struct multiboot_mmap_entry {
    uint32_t size;            // Tamanho DESTA estrutura
    uint64_t addr;            // Endereço base da região
    uint64_t len;             // Tamanho da região
    uint32_t type;            // Tipo: 1 = usável, outros = reservado
} __attribute__((packed)) multiboot_mmap_entry_t;

#endif
