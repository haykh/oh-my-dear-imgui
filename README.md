# Oh My Dear ImGui (OMDI)

A bit more than minimal wrapper library for ImGui-based applications.

## Usage

### Cross-compiling OMDI

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

### Using in applications

Below is a minimal example for using OMDI in your application:

```cpp
#include <omdi.hpp> // import the main omdi header

auto main() -> int {
  auto state = omdi::state::State(); // define the application state
  auto app   = omdi::app::App(&state); // define the application object

  app.Init(&state); // initialize the application
  app.Render(&state); // enter the render loop

  return 0;
}
```

You can also use some or all of the built-in components by passing them to the app renderer which will process these automatically:

```cpp
// managers
auto pickerDialogManager = omdi::picker::PickerManager();
auto toastManager        = omdi::toasts::ToastManager();
auto fontManager         = omdi::fonts::FontManager();
auto screenshotManager   = omdi::save::ScreenshotManager();

// ui elements
auto styleDialog = omdi::config::StyleDialog();
auto menubar     = omdi::menubar::Menubar();

auto components = omdi::components_t {
  {      "menubar",     &menubar },
  { "style_dialog", &styleDialog }
};
auto managers = omdi::managers_t {
  {      "toast_manager",        &toastManager },
  {       "font_manager",         &fontManager },
  { "screenshot_manager",   &screenshotManager },
  {     "picker_manager", &pickerDialogManager }
};

app.Init(&state, managers);

app.Render(
  &state,
  [&]() {
    // custom rendering routine
  },
  components,
  managers);
```

### Examples

A few standalone examples can be found in the `examples/` directory. These can be compiled using simply:

```sh
cmake -B build
cmake --build build -j
```

from the root of the repository.


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
- [x] image export (via [`stb`](https://github.com/nothings/stb))
- [ ] support for other backends
