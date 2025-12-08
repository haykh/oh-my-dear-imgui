{
  pkgs ? import <nixpkgs> { },
  py ? "313",
}:

pkgs.mkShell rec {
  name = "omdi-docs";
  nativeBuildInputs = with pkgs; [
    pkgs."python${py}"
    pkgs."python${py}Packages".pip
    black
    pyright
    taplo
    vscode-langservers-extracted
    zlib
  ];
  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
    pkgs.stdenv.cc.cc
    pkgs.zlib
  ];

  shellHook = ''
    if [ ! -d ".venv" ]; then
      python3 -m venv .venv
      source .venv/bin/activate
      pip3 install -r requirements.txt
    else
      source .venv/bin/activate
    fi
    echo "${name} nix-shell activated: $(which python)"
  '';
}
