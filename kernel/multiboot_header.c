#include <stdint.h>

#define MULTIBOOT_HEADER_MAGIC  0x1BADB002
#define MULTIBOOT_HEADER_FLAGS  0x00000003
#define CHECKSUM                -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

struct multiboot_header {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} __attribute__((packed));

__attribute__((section(".multiboot")))
struct multiboot_header multiboot_hdr = {
    .magic = MULTIBOOT_HEADER_MAGIC,
    .flags = MULTIBOOT_HEADER_FLAGS,
    .checksum = CHECKSUM
};

