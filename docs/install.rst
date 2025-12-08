Installation & Usage
======================

Dependencies
-----------------

Following dependencies are built in-tree:

- ``Plog``
- ``toml11``
- ``stb``
- ``ImGui``
- ``ImPlot``
- ``ImGuiFileDialog``

Following dependencies are assumed to be installed on the system:

- ``glfw3``
- ``OpenGL``

.. _preinstall:

Pre-installing
-----------------

You can compile and install ``oh-my-dear-imgui`` using the install script:

.. code-block:: shell
   
  ./install.sh [-h]

In which case the library will be installed in ``$HOME/.omdi``, or you can do that manually

.. code-block:: shell

  cmake -B build
  cmake --build build --config Release -j $(nproc)
  cmake --install build --prefix=/install-path-for/omdi/

.. tip::

  Make sure to clone the repository with all the submodules if doing things manually:

  .. code-block:: shell
    
    git clone --recurse-submodules -j $(nproc)

  If you have already cloned the repository without the submodules, you can initialize them using:

  .. code-block:: shell
    
    git submodule update --init --recursive -j $(nproc)


After the library is compiled and installed, you can add it as a dependency to your app:

.. code-block:: cmake
  :emphasize-lines: 1, 7
  :caption: CMakeLists.txt

  find_package(oh-my-dear-imgui CONFIG REQUIRED)

  set(EXEC main)
  set(SRC main.cpp)
  add_executable(${EXEC} ${SRC})

  target_link_libraries(${EXEC} PRIVATE oh-my-dear-imgui::oh-my-dear-imgui)

And simply point to the install directory when compiling your application:

.. code-block:: shell
   
  cmake -B build -D CMAKE_PREFIX_PATH=/install-path-for/omdi/

In-tree building
~~~~~~~~~~~~~~~~~~~~

Alternatively, you can fetch OMDI as part of your build using `FetchContent` to build the library in-tree:

.. code-block:: cmake
  :caption: CMakeLists.txt

  set(FETCHCONTENT_QUIET FALSE)
  include(FetchContent)
  FetchContent_Declare(
        oh-my-dear-imgui
        GIT_REPOSITORY https://github.com/haykh/oh-my-dear-imgui.git
        GIT_TAG master
        GIT_PROGRESS TRUE)
  FetchContent_MakeAvailable(oh-my-dear-imgui)

  set(EXEC main)
  set(SRC main.cpp)
  add_executable(${EXEC} ${SRC})

  target_link_libraries(${EXEC} PRIVATE oh-my-dear-imgui::oh-my-dear-imgui)

.. warning::

  This typically takes a couple of minutes though, so is not recommended.

Usage
-----------------

Below is a minimal example for using OMDI in your application:

.. code-block:: cpp

  #include <omdi.hpp> // import the main omdi header

  auto main() -> int {
    auto state = omdi::State(); // define the application state
    auto app   = omdi::App(&state); // define the application object

    app.Init(&state); // initialize the application
    app.Render(&state); // enter the render loop

    return 0;
  }

You can also use some or all of the built-in components by passing them to the app renderer which will process these automatically:

.. code-block:: cpp

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
    managers
  );


Examples
~~~~~~~~~~~~~~

A few standalone examples can be found in the ``examples/`` directory. These can be compiled using simply:

.. code-block:: shell

  cmake -B build -D omdi_BUILD_EXAMPLES=ON
  cmake --build build -j

from the root of the repository.
