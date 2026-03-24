# portugolOS

Um kernel experimental para estudo de sistemas operacionais, usando portugol como tema e piada.

> Este projeto é apenas para fins de aprendizado.

---

## Requisitos

Este projeto **não usa o compilador padrão do sistema**. É necessário um cross-compiler para x86 32-bit:

| Ferramenta | Obrigatório |
|---|---|
| `i686-elf-gcc` | sim |
| `i686-elf-ld` | sim |
| `grub-mkrescue` | sim |
| `qemu-system-i386` | opcional (para testes) |

### Por quê cross-compiler?

Um kernel não roda sobre Linux e não tem acesso à libc. O `i686-elf-gcc` gera binários *freestanding* no formato ELF, compatíveis com GRUB e com o linker script do projeto.

---

## Como compilar

Com o toolchain no PATH:
```bash
make
make iso
make run
# ou diretamente:
qemu-system-i386 -cdrom portugolOS.iso
```

---

## Estrutura do projeto

TODO
