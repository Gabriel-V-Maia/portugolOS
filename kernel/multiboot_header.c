__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
    0x1BADB002,             // magic
    0x0,                    // flags
    -(0x1BADB002)           // checksum
};

