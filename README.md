# ImGui Boilerplate

A bit more than minimal boilerplate code for ImGui-based applications.

## Usage

```sh
# compile
cmake -B build
cmake --build build -j

# run
./build/src/imgui-boilerplate.xc
```

## In-tree dependencies

Following depedencies are built in-tree:

- `Plog`
- `toml11`
- `ImGui`
- `ImPlot`
- `ImGuiFileDialog`

## External dependencies

Following depedencies are assumed to be installed on the system:

- `glfw3`
- `OpenGL`

## Features

- dependencies can be built from the downloaded submodules or fetched with `CMake` at compile time;
- includes basic manager classes for picker dialogs, toasts (notifications), etc.
- includes basic ui component classes, e.g., menubars, etc.
- includes external font/icon support (see `src/assets/`);
- includes some third-party `ImGui` plugins (also built in-tree): `ImPlot`, `ImGuiFileDialog`.

## TODO

- [x] notifications (via [`ImGuiNotify`](https://github.com/TyomaVader/ImGuiNotify))
- [ ] custom `ImPlot` renderers
- [ ] image export (via [`stb`](https://github.com/nothings/stb))
