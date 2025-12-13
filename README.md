# portugolOS

Um kernel experimental feito para estudar sistemas operacionais, usando portugol como uma piada msm.

## Requisitos

Este projeto **não usa o compilador padrão do sistema**.

É necessário um cross-compiler para kernel x86 32-bit:

- `i686-elf-gcc`
- `i686-elf-ld`
- `grub-mkrescue`
- `qemu-system-i386` (opcional, para testes)

## Por quê?

Um kernel não roda sobre Linux nem usa libc.  
O `i686-elf-gcc` gera binários *freestanding* no formato ELF, compatíveis com GRUB e com o linker script do projeto.

## Como compilar

Com o toolchain no PATH:

```bash
make
make iso
make run ou qemu-system-i386 -cdrom portugolOS.iso
```

Então o qemu vai rodar o sistema.

# Estrutura para desenvolver o OS

TODO

