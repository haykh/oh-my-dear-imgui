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

   Prepares ImGui and any
