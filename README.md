# Oh My Dear ImGui (OMDI)

A bit more than minimal wrapper library for ImGui-based applications.

## Usage

Add the library as a dependency to your app in your `CMakeLists.txt`:

```cmake
set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)
FetchContent_Declare(
  oh-my-dear-imgui
  GIT_REPOSITORY https://github.com/haykh/oh-my-dear-imgui.git
  GIT_TAG master
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(oh-my-dear-imgui)
```

Then simply link with it:

```cmake
set(EXEC main)
set(SRC main.cpp)
add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} PRIVATE oh-my-dear-imgui)
```

## Dependencies

Following depedencies are built in-tree:

- `Plog`
- `toml11`
- `stb`
- `ImGui`
- `ImPlot`
- `ImGuiFileDialog`

Following depedencies are assumed to be installed on the system:

- `glfw3`
- `OpenGL`

## Features

- basic manager classes for picker dialogs, toasts (notifications), screenshots, fonts, etc.;
- basic ui component classes, e.g., menubars, etc.;
- app state with optional conversion to/from toml;
- functionality for error handling (safe rendering + error notification) at runtime;
- external font/icon support (see `src/assets/`);
- dependencies can be built from the downloaded submodules or fetched with `CMake` at compile time;
- includes some third-party `ImGui` plugins (also built in-tree): `ImPlot`, `ImGuiFileDialog`.

## TODO

- [ ] documentation
- [x] notifications (via [`ImGuiNotify`](https://github.com/TyomaVader/ImGuiNotify))
- [ ] custom `ImPlot` renderers
- [ ] image export (via [`stb`](https://github.com/nothings/stb))
- [ ] support for other backends
