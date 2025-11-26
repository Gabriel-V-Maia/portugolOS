# ===============================
#  portugolOS — Makefile
# ===============================

# ---- Toolchain ----
CC = i686-elf-gcc
LD = i686-elf-ld

CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -m elf_i386

# ---- Source files ----
KERNEL_SRC = $(shell find kernel -name '*.c')

KERNEL_OBJ = $(KERNEL_SRC:.c=.o)

# ===============================
#  Build targets
# ===============================

all: kernel.bin

kernel.bin: $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -T kernel/linker.ld -o $@ $(KERNEL_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Build ISO ----
iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp boot/grub.cfg iso/boot/grub/
	grub-mkrescue -o portugolOS.iso iso/

# ---- Run in QEMU ----
run: iso
	qemu-system-i386 -cdrom portugolOS.iso -m 64M

# ---- Clean build ----
clean:
	rm -rf kernel/*.o kernel.bin iso portugolOS.iso

