{
  pkgs ? import <nixpkgs> { },
}:

let
  name = "oh-my-dear-imgui";
in
pkgs.mkShell {

  name = "${name}-env";
  nativeBuildInputs = with pkgs; [
    zlib
    cmake

    libgcc
    clang-tools
    glfw

    cmake-format
    cmake-lint
    neocmakelsp
    taplo
    vscode-langservers-extracted
  ];

  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath ([
    pkgs.stdenv.cc.cc
    pkgs.zlib
  ]);

  shellHook = ''
    BLUE='\033[0;34m'
    NC='\033[0m'

    echo -e "${name} nix-shell activated"
  '';

}
