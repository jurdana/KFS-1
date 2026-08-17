{
  description = "KFS-1"; # project description

  inputs = {
    # nixpkgs is the main Nix package repository
    # nixos-24.05 is a stable release - pinned for reproducibility
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-24.05";
  };

  outputs = { self, nixpkgs}: 
    let
      # shorthand for the x86_64-linux package set
      # avoids repeating nixpkgs.legacyPackages.x86_64-linux everuwhere
      pkgs = nixpkgs.legacyPackages.x86_64-linux;

      # cross-compiler targeting bare-metal i386 (i686-elf)
      # pkgsCross.i686-embedded : selects the i686 embedded target
      # buildPackages.gcc       :gets the GCC compiler for that target
      # produces the i686-elf-gcc binary used to compile the kernel
      crossGcc = nixpkgs.legacyPackages.x86_64-linux.pkgsCross.i686-embedded.buildPackages.gcc;
    in
    {
      # defines the default development shell for x86_64-linux
      # activated with: nix develop
      devShells.x86_64-linux.default = pkgs.mkShell {
        packages = [
          pkgs.nasm     # assembler - compiles boot.asm
          pkgs.qemu     # emulator - runs the kernel ISO
          crossGcc      # i686-elf-gcc - cross-compiles C sources for i386
          pkgs.grub2    # provides grub-mkrescue - generates the bootable ISO
          pkgs.xorriso  # required by grub-mkrescue to build the ISO image
        ];
      };
    };
}