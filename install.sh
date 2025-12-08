#!/usr/bin/env bash

DEFAULT_INSTALL_DIR="$HOME/.omdi"

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

print_help() {
  echo -e "${BLUE}oh-my-dear-imgui${NC} installation script"
  echo ""
  echo "Usage: $0 [options]"
  echo ""
  echo "Options:"
  echo "  -i, --install <directory>   Specify the installation directory (default: $DEFAULT_INSTALL_DIR)"
  echo "  -e, --examples              Build the examples"
  echo "  -h, --help                  Show this help message and exit"
}

INSTALL_DIR="$DEFAULT_INSTALL_DIR"
BUILD_EXAMPLES="OFF"

while [[ "$#" -gt 0 ]]; do
  case $1 in
  -i | --install)
    INSTALL_DIR="$2"
    shift 2
    ;;
  -e | --examples)
    BUILD_EXAMPLES="ON"
    shift
    ;;
  -h | --help)
    print_help
    exit 0
    ;;
  *)
    echo "Unknown option: $1"
    print_help
    exit 1
    ;;
  esac
done

echo -e "${BLUE}oh-my-dear-imgui${NC} will be built and installed to: $INSTALL_DIR"
echo "---------------------------------------------------"

echo -e "1. Configuring ${BLUE}oh-my-dear-imgui${NC}"
echo "==================================================="

cmake -B build -D omdi_BUILD_EXAMPLES="$BUILD_EXAMPLES" -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX="$INSTALL_DIR" || {
  echo -e "${RED}CMake configuration failed${NC}"
  exit 1
}

echo "==================================================="
echo -e "2. Compiling ${BLUE}oh-my-dear-imgui${NC}"
echo "==================================================="

cmake --build build --config Release -j $(nproc) || {
  echo -e "${RED}Build failed${NC}"
  exit 1
}

echo "==================================================="
echo -e "3. Installing ${BLUE}oh-my-dear-imgui${NC} to $INSTALL_DIR"
echo "==================================================="

cmake --install build --prefix "$INSTALL_DIR" || {
  echo -e "${RED}Installation failed${NC}"
  exit 1
}

if [ "$BUILD_EXAMPLES" == "ON" ]; then
  EXAMPLES_DIR="$INSTALL_DIR/bin"
  mkdir -p "$EXAMPLES_DIR" || {
    echo -e "${RED}Failed to create examples directory at $EXAMPLES_DIR${NC}"
    exit 1
  }
  cp build/examples/example-* "$EXAMPLES_DIR"/ || {
    echo -e "${RED}Failed to copy example binaries to $EXAMPLES_DIR${NC}"
    exit 1
  }
fi

echo "==================================================="
echo -e "${BLUE}oh-my-dear-imgui${NC} installed to $INSTALL_DIR"
