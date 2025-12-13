
# ===============================
#  portugolOS — Makefile
# ===============================

# ---- Toolchain ----
CC  = i686-elf-gcc
LD  = i686-elf-ld
AS  = i686-elf-as

# ---- Flags ----
CFLAGS  = -m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -m elf_i386

# ---- Sources ----
C_SRC   = $(shell find kernel -name '*.c')
ASM_SRC = boot/boot.s

C_OBJ   = $(C_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.s=.o)

OBJS = $(ASM_OBJ) $(C_OBJ)

# ===============================
#  Build targets
# ===============================

all: kernel.bin

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -T kernel/linker.ld -o $@ $(OBJS)

# ---- Compile C ----
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Assemble ASM ----
%.o: %.s
	$(AS) $< -o $@

# ---- Build ISO ----
iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp boot/grub.cfg iso/boot/grub/
	grub-mkrescue -o portugolOS.iso iso/

# ---- Run in QEMU ----
run: iso
	qemu-system-i386 -cdrom portugolOS.iso -m 64M

# ---- Clean ----
clean:
	find kernel boot -name '*.o' -delete
	rm -rf kernel.bin iso portugolOS.iso


