# Oh My Dear ImGui (OMDI)

A bit more than minimal wrapper library for ImGui-based applications.

## Usage

_@TODO_

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
- basic manager classes for picker dialogs, toasts (notifications), fonts, etc.;
- basic ui component classes, e.g., menubars, etc.;
- app state with optional conversion to/from toml;
- functionality for error handling (safe rendering + error notification) at runtime;
- external font/icon support (see `src/assets/`);
- includes some third-party `ImGui` plugins (also built in-tree): `ImPlot`, `ImGuiFileDialog`.

## TODO

- [ ] documentation
- [x] notifications (via [`ImGuiNotify`](https://github.com/TyomaVader/ImGuiNotify))
- [ ] custom `ImPlot` renderers
- [ ] image export (via [`stb`](https://github.com/nothings/stb))
