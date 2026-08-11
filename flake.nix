{
  description = "KFS-1";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-24.05";
  };

  outputs = { self, nixpkgs}: 
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
      crossGcc = nixpkgs.legacyPackages.x86_64-linux.pkgsCross.i686-embedded.buildPackages.gcc;
    in
      {
    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = [
        pkgs.nasm
        pkgs.qemu
        crossGcc
        pkgs.grub2
        pkgs.xorriso
      ];
    };
  };
}
