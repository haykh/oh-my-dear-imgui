.. _omdi-app:

App
===

.. cpp:namespace:: omdi

Overview
--------

.. cpp:class:: App

   Main class for the ``omdi`` application.

   The :cpp:class:`omdi::App` class owns the main GLFW window and integrates
   the ImGui context. It manages the main render loop and provides a simple
   interface to:

   - initialize the application with an :cpp:class:`omdi::State` instance,
   - optionally register managers and UI components,
   - run a render loop with a user-provided rendering callback,
   - access the underlying GLFW window, ImGui IO, and GLSL version string.

Usage example
-------------

Basic setup and render loop:

.. code-block:: cpp

  auto state = omdi::State();

  // Construct the application window
  auto app = omdi::App(&state, "omdi Example", /*swapInterval=*/1, /*isResizable=*/true);

  // Initialize managers if needed (empty by default)
  app.Init(&state);

  // Main loop
  app.Render(&state, [&]() {
    // Simple render callback
  });


Public interface
----------------

Constructor and destructor
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: App::App(omdi::state::State* state, \
                           const std::string& name = "omdi App", \
                           int swapInterval = 1, \
                           bool isResizable = true)

   Construct the main application object and create the underlying window.

   :param state: Pointer to the global state manager.
   :param name: Window title (defaults to ``"omdi App"``).
   :param swapInterval: Swap interval for VSync (typically ``0`` or ``1``).
   :param isResizable: Whether the window is resizable by the user.

   The constructor is responsible for setting up GLFW, the window,
   ImGui context, and any required graphics state.

.. cpp:function:: App::~App()

   Destroy the application object and release associated resources.

   Cleans up the GLFW window and ImGui context, and performs any
   necessary shutdown for the underlying graphics APIs.

Main loop helpers
~~~~~~~~~~~~~~~~~

.. cpp:function:: void App::processInput()

   Process user input events.

   Typically polls GLFW (keyboard, mouse, window events) and updates
   internal state / ImGui IO accordingly. Should be called once per frame.

.. cpp:function:: bool App::startFrame()

   Begin a new frame.

   Prepares ImGui and any rendering state for a new frame.

   :returns: ``true`` if the frame should proceed, ``false`` if the
             application is shutting down or the window should close.

.. cpp:function:: void App::renderFrame()

   Render the current frame.

   Issues drawing commands for ImGui and any additional application
   rendering. This is usually called between :cpp:func:`omdi::App::startFrame`
   and :cpp:func:`omdi::App::endFrame`.

.. cpp:function:: void App::endFrame(int& width, int& height, ImVec4& clear_color)

   Finalize the current frame and present it to the screen.

   :param width: Output parameter receiving the current framebuffer width.
   :param height: Output parameter receiving the current framebuffer height.
   :param clear_color: Clear color used for the frame; may be read or updated.

   This function typically handles buffer swapping and any per-frame
   housekeeping related to the window size and clear color.

Initialization and render loop
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: void App::Init(omdi::state::State* state, \
                                 const std::map<std::string, void*>& managers = {})

   Initialize the omdi application with the given state and optional managers.

   :param state: Pointer to the global state manager.
   :param managers: Map of optional omdi managers, keyed by string identifiers.
                    The exact types pointed to by the values are application-specific.

   This function can be used to register subsystems (e.g. logging, resource
   managers, backends) that the application and UI components can access
   through the shared :cpp:class:`omdi::state::State` or other mechanisms.

.. cpp:function:: void App::Render(omdi::state::State* state, \
                                   const std::function<void()>& custom_render = nullptr, \
                                   const std::map<std::string, void*>& components = {}, \
                                   const std::map<std::string, void*>& managers = {})

   Run the main render loop using the provided state, optional custom render
   callback, UI components, and managers.

   :param state: Pointer to the global state manager.
   :param custom_render: User-provided callback invoked each frame to perform
                         custom rendering (e.g. ImGui windows, scene drawing).
                         If ``nullptr``, only the built-in omdi components/managers
                         are rendered.
   :param components: Map of optional omdi UI components, keyed by string identifiers.
   :param managers: Map of optional omdi managers, keyed by string identifiers.

   Internally, :cpp:func:`omdi::App::Render` typically loops until
   :cpp:func:`omdi::App::windowShouldClose` returns non-zero, calling
   :cpp:func:`omdi::App::processInput`, :cpp:func:`omdi::App::startFrame`,
   the *custom_render* callback (if provided), :cpp:func:`omdi::App::renderFrame`,
   and :cpp:func:`omdi::App::endFrame` each frame.

Window and context accessors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: int App::windowShouldClose() const

   Check whether the window should close.

   :returns: Non-zero if the user requested to close the window (e.g. via the
             window close button), zero otherwise.

   This is a thin wrapper around :cpp:func:`glfwWindowShouldClose`.

.. cpp:function:: GLFWwindow* App::window() const

   Get the underlying GLFW window handle.

   :returns: Pointer to the :cpp:class:`GLFWwindow` owned by the application.

   This may be useful for low-level integration with other libraries that
   operate directly on the GLFW window.

.. cpp:function:: ImGuiIO* App::io()

   Get the ImGui IO object associated with this application.

   :returns: Pointer to the :cpp:class:`ImGuiIO` instance used by ImGui.

   Use this to access input state, configuration flags, or other ImGui
   IO properties.

.. cpp:function:: const char* App::glsl_version() const

   Get the GLSL version string used by the application.

   :returns: Null-terminated string describing the GLSL version
             (e.g. ``"#version 130"``), suitable for use in shader source.

Notes
-----

- :cpp:class:`omdi::App` assumes that GLFW and ImGui are available and correctly
  configured in your build environment.
- The :cpp:func:`omdi::App::Render` method is the main entry point for running
  the application’s render loop; for more advanced control, you can instead
  write your own loop using :cpp:func:`omdi::App::processInput`,
  :cpp:func:`omdi::App::startFrame`, :cpp:func:`omdi::App::renderFrame`,
  and :cpp:func:`omdi::App::endFrame` directly.
