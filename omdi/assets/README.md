This is a script which downloads fonts in binary (ttf) and converts them into header files (located in `generated/`).

## Usage

Just add your own fonts with relevant links into the makefile and run the make:

```sh
make
```

Once the `generated/FONT.h` file is generated, this can be used in the code:

```c++
#include "assets/generated/FONT.h"

Window::Window(...) {
  // ... 
  ImFontConfig font_config;
  font_config.PixelSnapH = true;

  auto io = &ImGui::GetIO();
  io->Fonts->Clear();
  io->Fonts->AddFontFromMemoryCompressedTTF(
    FONT_compressed_data,
    FONT_compressed_size,
    size,
    &font_config);
  io->Fonts->Build();
  // ...
}
```
