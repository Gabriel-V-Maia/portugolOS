ENTRY(kernel_main)

SECTIONS
{
    . = 0x100000;  
    
    kernel_start = .;
    
    .multiboot : {
        *(.multiboot)
    }
    
    .text : {
        *(.text)
    }
    
    .rodata : {
        *(.rodata)
    }
    
    .data : {
        *(.data)
    }
    
    .bss : {
        *(.bss)
        *(COMMON)
    }
    
    kernel_end = .;
}

