.global _start
.extern kernel_main

_start:
    cli
    mov $stack_top, %esp

    push %ebx    # multiboot_info*
    push %eax    

    call kernel_main

.hang:
    hlt
    jmp .hang

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:

