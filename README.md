# kfs-1

A minimal x86 kernel built from scratch, bootable via GRUB.

## Overview

kfs-1 is the first project of the Kernel From Scratch series. The goal is to build a kernel from the ground up, without any existing OS, API, or standard library. The kernel boots via GRUB using the Multiboot protocol, initializes a VGA text mode interface, and displays output on screen.

## Requirements

- [Nix](https://nixos.org/) with flakes enabled
- QEMU (provided by the Nix environment)

## Getting started

Enter the development environment:

```sh
nix develop
```

Build the kernel ISO:

```sh
make
```

Run in QEMU:

```sh
make run
```

## Project structure

```
kfs-1/
├── boot/
│   └── boot.asm        # ASM entry point, Multiboot header, stack setup
├── drivers/
│   └── vga.c           # VGA text mode driver (direct memory write to 0xB8000)
├── kernel/
│   └── kmain.c         # Kernel entry point
├── include/
│   └── vga.h           # VGA driver interface
├── iso/
│   └── boot/
│       ├── grub/
│       │   └── grub.cfg    # GRUB configuration
│       └── kernel.bin      # Kernel binary (generated)
├── obj/                # Object files (generated)
├── flake.nix           # Nix development environment
├── linker.ld           # Custom linker script
└── Makefile
```

## Implementation details

### Boot sequence

1. GRUB reads `grub.cfg` and loads `kernel.bin` using the Multiboot protocol
2. GRUB jumps to `_start` defined in `boot.asm`
3. `_start` initializes the stack and calls `kmain`
4. If `kmain` returns, the CPU is halted in an infinite loop

### Multiboot header

The Multiboot header is placed at the very beginning of the binary (within the first 8 KB) so GRUB can identify the binary as a valid kernel. It consists of three 32-bit values: a magic number (`0x1BADB002`), flags (`0x0`), and a checksum.

### VGA text mode

The VGA driver writes directly to the memory buffer at `0xB8000`. Each character on screen occupies 2 bytes: one for the ASCII character and one for the color attribute (4 bits background, 4 bits foreground). The screen is 80 columns by 25 lines.

### Linker script

The custom linker script places the kernel at address `0x100000` (1 MB), which is the standard load address for i386 kernels with GRUB. The Multiboot header section is forced first in the `.text` section.

### Compilation

The kernel is compiled for the `i386` architecture using a bare-metal cross-compiler (`i686-elf-gcc`) with the following flags:

| Flag | Purpose |
|---|---|
| `-fno-builtin` | Disable GCC built-in functions |
| `-fno-stack-protector` | Disable stack protection (no runtime support) |
| `-nostdlib` | No standard library |
| `-nodefaultlibs` | No default libraries |
| `-ffreestanding` | Freestanding environment (linking only) |

## Development environment

The Nix flake provides the full toolchain:

| Tool | Purpose |
|---|---|
| `i686-elf-gcc` | Cross-compiler targeting bare-metal i386 |
| `nasm` | Assembler for boot.asm |
| `grub-mkrescue` | Generates the bootable ISO |
| `xorriso` | ISO generation dependency |
| `qemu-system-i386` | Emulator for testing |

## Makefile targets

| Target | Description |
|---|---|
| `make` / `make all` | Build the kernel ISO |
| `make run` | Build and launch in QEMU |
| `make clean` | Remove object files |
| `make fclean` | Remove all generated files |
| `make re` | Full rebuild |
