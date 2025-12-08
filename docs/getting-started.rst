Getting Started
=================

Let's start with a minimal example of how to set up and use ``oh-my-dear-imgui`` in your project, assuming you have already installed the library as described in the :ref:`preinstallation section <preinstall>`.

Setting up the project
----------------------

Start by making a source cpp file, ``main.cpp``, and a ``CMakeLists.txt`` file in the same directory. 

.. code-block:: cmake
  :caption: CMakeLists.txt

  set(NAME omdi-demo)

  project(${NAME})

  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  find_package(oh-my-dear-imgui CONFIG REQUIRED)

  set(SRC main.cpp)
  add_executable(${NAME} ${SRC})

  target_link_libraries(${NAME} PRIVATE oh-my-dear-imgui::oh-my-dear-imgui)


.. code-block:: cpp
  :caption: main.cpp

  #include <omdi.hpp> // import the main omdi header

  auto main() -> int {
    auto state = omdi::State(); // define the application state
    auto app   = omdi::App(&state); // define the application object

    app.Init(&state); // initialize the application
    app.Render(&state); // enter the render loop

    return 0;
  }

Let's break down the code. The ``CMakeLists.txt`` is a helper file for actually compiling the project. If you have never used ``CMake`` before, you can read more about it `here <https://cmake.org/cmake/help/latest/guide/tutorial/index.html>`_. The important thing here is that we create a project using a variable ``NAME``, we then fetch the ``oh-my-dear-imgui`` package using the ``find_package`` function. Then we declare an executable using ``add_executable``, which will be built from the source file ``main.cpp``, and then tell the compiler to link against the ``oh-my-dear-imgui`` library using ``target_link_libraries``.

The ``main.cpp`` file is the actual source code for our application. We start by including the main ``omdi`` header file, which exposes all the functionality of the library. Then we define the ``main`` function, which is the entry point of any C++ program.

Inside the ``main`` function, we first create an instance of ``omdi::State``, which represents the application state. This state can be used to store various settings and data for the application (more on that later). Next, we create an instance of ``omdi::App``, passing a pointer to the state we just created. This ``App`` object is responsible for managing the application lifecycle, including initialization and rendering.

After creating the ``App`` object, we initialize it by calling ``app.Init(&state)``, which sets up the necessary resources and configurations for the application. Finally, we enter the rendering loop by calling ``app.Render(&state)``, which will keep the application running and rendering until it is closed.

To compile and run the application, navigate to the directory containing your ``CMakeLists.txt`` and ``main.cpp`` files in your terminal, and execute the following commands:

.. code-block:: shell

  cmake -B build -D CMAKE_PREFIX_PATH=$HOME/.omdi/ # adjust the path as needed
  cmake --build build -j $(nproc)
  ./build/omdi-demo

If everything goes well, you should see an empty window popping up! You can safely close it for now using the Escape key or the window's close button.

To test that it indeed renders ImGui, you can add a simple ``ImGui`` window in the render loop. Modify the ``Render`` call as follows:

.. code-block:: cpp

  app.Render(&state, [&]() {
    ImGui::ShowDemoWindow();
  });

Don't forget to recompile, and then run the application again. You should now see the classic ``ImGui`` demo window! That second argument that we passed to ``Render`` is a lambda function that gets called every frame, allowing us to add anything we like to be executed every time a frame is rendered.

Adding a menubar
----------------

``omdi`` comes pre-packaged with various useful UI components, the central of which is the menubar. To add it, simply declare it somewhere before calling the ``Init()`` function:

.. code-block:: cpp

  auto menubar    = omdi::menubar::Menubar();
  auto components = omdi::components_t {
    { "menubar", &menubar }
  };

  app.Render(&state, [&]() {
    ImGui::ShowDemoWindow();
  }, components);

Because we will be adding more components later, we first create a dicitionary of components called ``components``, and add the menubar to it. Then we pass this dictionary as the third argument to the ``Render`` function. Now, when you compile and run the application, you should see an empty menubar at the top of the window.

We can customize the menubar by adding menus and items to it. For instance, let's add a toggle to switch the ``ImGui`` demo window on and off. The safest way to keep track of the state of the demo window is to use our state variable, so let's add a boolean entry to it (e.g., after defining the ``state`` variable):

.. code-block:: cpp
  :emphasize-lines: 2

  auto state = omdi::State();
  state.set("show_imgui_demo", false);

Now, let's add a "Help" menu to the left of the menubar with a toggle item for the demo window:

.. code-block:: cpp

  auto menubar = omdi::menubar::Menubar();
  menubar.AddLeft([&]() {
    omdi::safe::Component(
      []() {
        return ImGui::BeginMenu("Help");
      },
      [&]() {
        ImGui::Checkbox("Show ``ImGui`` demo", &state.get<bool>("show_imgui_demo"));
      },
      []() {
        ImGui::EndMenu();
      });
  });

Notice, that we are essentially passing a lambda function to the ``AddLeft`` method, which calls a special built-in function ``omdi::safe::Component``. The component function itself takes three delta functions: the initialization (which must returns the status of ``ImGui::BeginMenu`` -- a built-in ``ImGui`` function to create a menu), the main rendering routine (where we add our checkbox), and the finalization (which calls ``ImGui::EndMenu``). The checkbox itself is bound to the state variable we created earlier via the ``state.get<bool>`` call, so it will automatically update the state when toggled. This is the recommended way of adding custom UI elements to ``omdi`` components, as it ensures that any errors during rendering are caught and displayed as notifications (toasts, coming up later) instead of crashing the application. It also ensures that any code execution does not interfere with the rest of the UI rendering.

Ok, finally, we need to modify our render loop to only display the demo window when the corresponding state variable is true:

.. code-block:: cpp
  :emphasize-lines: 2, 4

  app.Render(&state, [&]() {
    if (state.get<bool>("show_imgui_demo")) {
      ImGui::ShowDemoWindow(&state.get<bool>("show_imgui_demo"));
    }
  }, components);

Note, that we are passing a pointer to the state variable so that the ``ImGui`` demo window can automatically close it through its built-in close button. Now, when you compile and run the application, you should see a "Help" menu in the menubar. Clicking on it will reveal a "Show ``ImGui`` demo" checkbox, which you can toggle to show or hide the ``ImGui`` demo window.

.. hint::

  ``omdi`` closely follows the design principles of Dear ImGui, so in that sense adding any ``ImGui`` element as an ``omdi::safe::component`` is fairly straightforward.

Adding ``ImGui`` components
----------------------------

Adding any other ``ImGui`` elements to the application is as simple as putting them inside the render function. For example, let's create a simple window with a text and a color picker which stores the color in the application state. First of all, let's add the state variable to hold the color (after defining the ``state`` variable):

.. code-block:: cpp

  state.set("my_color", new float[4] { 0.0f, 0.5f, 0.5f, 1.0f });

Next, inside the render loop, let's add a new window with the following components:

.. code-block:: cpp

  app.Render(&state, [&]() {
    // ... 
    if (ImGui::Begin("Test Window")) {
      ImGui::Text("Pick a random color");
      ImGui::ColorEdit4("Color", state.get<float*>("my_color"));
      const auto color = state.get<float*>("my_color");
      ImGui::Text("You picked: %.2f, %.2f, %.2f, %.2f",
                  color[0],
                  color[1],
                  color[2],
                  color[3]);
      ImGui::End();
    }
  }, components);
 
.. hint::

  The best way to find all the components for Dear ``ImGui`` is to check out their `official interactive demo <https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html>`_, which conveniently links each component to the relevant sections of the code.

Customizing the UI
--------------------

``omdi`` comes with a set of UI configuration tools to modify the look and feel of the application at runtime. This is done through the built-in ``StyleDialog`` component, which can be added to the application in a similar way as the menubar.

.. code-block:: cpp
  :emphasize-lines: 1, 5

  auto styleDialog = omdi::config::StyleDialog();

  auto components = omdi::components_t {
    {      "menubar",     &menubar },
    { "style_dialog", &styleDialog }
  };

To control when the style dialog is shown, we can again add a toggle to the menubar, modifying a special attribute of the ``state`` variable called ``show_style_dialog`` when the menu item is clicked:

.. code-block:: cpp

  menubar.AddLeft([&]() {
    omdi::safe::Component(
      []() {
        return ImGui::BeginMenu("UI");
      },
      [&]() {
        if (ImGui::MenuItem("Style dialog")) {
          state.set("show_style_dialog", true);
        }
      },
      []() {
        ImGui::EndMenu();
      });
  });

If you compile and run -- you should be able to see a "UI" menu and a "Style dialog" item in it. Clicking on it will open the style configuration dialog, where you can pick one of the preset styles or change the background color. 

.. tip::

   Notice, that you can have multiple ``AddLeft``, ``AddCenter``, and ``AddRight`` calls to add more menus, which will automatically be stacked in the correct order.

Let's go further and add a font picker to the style dialog. By default, this setting is disabled to avoid unnecessary use of resources, but we can easily enable it by adding a font manager to the application. First, let's declare it before initializing the app and put it in the ``managers`` dictionary:

.. code-block:: cpp

  auto fontManager = omdi::fonts::FontManager();
  auto managers = omdi::managers_t {
    { "font_manager", &fontManager }
  };

Again, we will be able to add more managers later. Now, we need to pass the ``managers`` dictionary to both the ``Init`` and the ``Render`` functions:

.. code-block:: cpp
  :emphasize-lines: 1, 7

  app.Init(&state, managers);

  app.Render(&state, [&]() {
    // ...
  }, 
  components, 
  managers);

Now when you open the style dialog, you should see a new section to tweak the family and the size of the font used in the application.

Plotting with ``ImPlot``
---------------------------

``omdi`` comes with a few built-in plotting components, but also supports default ``ImPlot`` plotting functionality out of the box. For the purposes of this exercise, let's add four side-by-side plots: a line plot, a simple shaded plot, a bar plot, and a scatter plot. First of all, let's generate some mock data to plot:

.. code-block:: cpp

  const auto npointsNoisy = 20;
  auto       noisyX       = new float[npointsNoisy];
  auto       noisyY1      = new float[npointsNoisy];
  auto       noisyY2      = new float[npointsNoisy];
  for (auto i = 0; i < npointsNoisy; ++i) {
    noisyX[i]  = i * 0.05f;
    noisyY1[i] = 0.5f + 0.1f * ((float)rand() / RAND_MAX);
    noisyY2[i] = 0.5f + 0.1f * ((float)rand() / RAND_MAX);
  }

  const auto npointsShaded = 1000;
  auto       shadeXs       = new float[npointsShaded];
  auto       shadeYUps     = new float[npointsShaded];
  auto       shadeYDwns    = new float[npointsShaded];

  for (auto i = 0; i < npointsShaded; ++i) {
    shadeXs[i]    = i * 0.001f;
    shadeYUps[i]  = 0.75f + 0.2f * sinf(25 * shadeXs[i]);
    shadeYDwns[i] = 0.75f + 0.1f * cosf(25 * shadeXs[i]);
  }

Here we're using simple C++ pointers, but any STL container (e.g., ``std::vector``, or ``std::array``) would work just as well, as long as we have an access to the raw data pointer. ``ImPlot`` uses a very similar workflow as ``ImGui``; we first create a plotting context, the add individual plots inside it. Let's add the following code to the render loop:

.. code-block:: cpp
  :emphasize-lines: 3-6

  app.Render(&state, [&]() {
    // ...
    if (ImPlot::BeginSubplots("Plots", 2, 2, ImVec2(-1, -1))) {
      // plotting functions go here
      ImPlot::EndSubplots();
    }
  }, components, managers);

Here, we are creating a 2x2 grid of subplots that will automatically adjust to the size of the window (``ImVec2`` object is just a tuple of pixel sizes in ``x`` and ``y``, where ``-1`` means auto-adjustment). Now, let's fill in the individual plots one by one.

.. code-block:: cpp

  app.Render(&state, [&]() {
    // ...
    if (ImPlot::BeginSubplots("Plots", 2, 2, ImVec2(-1, -1))) {
      if (ImPlot::BeginPlot("NoisyPlot")) {
        ImPlot::PlotLine("Noisy", noisyX, noisyY1, npointsNoisy);
        ImPlot::EndPlot();
      }
      if (ImPlot::BeginPlot("ShadedPlot")) {
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.5f);
        ImPlot::PlotShaded("Shaded", shadeXs, shadeYUps, shadeYDwns, npointsShaded);
        ImPlot::PlotLine("Shaded", shadeXs, shadeYUps, npointsShaded);
        ImPlot::PlotLine("Shaded", shadeXs, shadeYDwns, npointsShaded);
        ImPlot::PopStyleVar();
        ImPlot::EndPlot();
      }
      if (ImPlot::BeginPlot("BarPlot")) {
        ImPlot::PlotBars("Bars", noisyY1, npointsNoisy);
        ImPlot::EndPlot();
      }
      if (ImPlot::BeginPlot("ScatterPlot")) {
        ImPlot::PlotScatter("Scatter", noisyY1, noisyY2, npointsNoisy);
        ImPlot::EndPlot();
      }
      ImPlot::EndSubplots();
    }
  }, components, managers);

The usage is fairly similar to ``ImGui``: you create a context (``BeginPlot``), add the plot components (``PlotLine``, ``PlotShaded``, etc.), and then close the context (``EndPlot``). Note that for the shaded plot, we are also pushing and popping a style variable to adjust the transparency of the shaded area. Other stuff, like legends, axis labels, shared axes, ticks, etc can be adjusted using the relevant ``ImPlot`` functions. Now, when you compile and run the application, you should see four different plots arranged in a 2x2 grid.


.. hint::

   Again, perhaps the best way to explore all the features of ``ImPlot`` is to check out their `interactive demo <https://traineq.org/implot_demo/src/implot_demo.html>`_.


You can also mix ``ImGui`` and ``ImPlot`` components freely. For example, let's adapt our previously defined color picker to change the color for all the lines in our subplots. 

.. code-block:: cpp
  :emphasize-lines: 2-5, 7

  if (ImPlot::BeginSubplots("Plots", 2, 2, ImVec2(-1, -1))) {
    auto color = state.get<float*>("my_color");
    ImGui::ColorEdit4("Color", color);
    ImPlot::PushStyleColor(ImPlotCol_Line,
                           ImVec4(color[0], color[1], color[2], color[3]));
    // plotting routines
    ImPlot::PopStyleColor();
    ImPlot::EndSubplots();
  }
  

GPU-accelerated 2D rendering with ``omdi``
------------------------------------------

``omdi`` includes a couple of built-in plotting functions, and one of them -- the 2D plotter -- is an order of magnitude faster than the built-in ``ImPlot`` heatmap functionality.

.. note::

  Currently, there are just two built-in plotters -- the ``PcolorPlot`` (for 2D rendering) and ``ScatterPlot``. More plotters will be added in future releases.

To use it, we first need to define the plotter object outside the render loop and bind some data to it. First, let's define some data:

.. code-block:: cpp

  const auto nx = 512u;
  const auto ny = 512u;
  auto       xs = new float[nx];
  auto       ys = new float[ny];

  for (auto i = 0u; i < nx; ++i) {
    xs[i] = i * 0.01f - 2.56f;
  }
  for (auto j = 0u; j < ny; ++j) {
    ys[j] = j * 0.015f;
  }

  auto zfunc = [](float x, float y, float t) {
    return std::sinf(x * (2.0 * M_PI) + t) *
           std::cosf(y * (2.0 * M_PI) + 1.5 * t) * std::expf(-4.0 * (x * x));
  };

  auto zs = new float[nx * ny];
  for (auto j = 0u; j < ny; ++j) {
    for (auto i = 0u; i < nx; ++i) {
      auto x         = xs[i];
      auto y         = ys[j];
      zs[j * nx + i] = zfunc(x, y, 0.0f);
    }
  }

Here we create a 2D grid of ``(x, y)`` coordinates and computed the corresponding ``z`` values from a simple function, ``zfunc``. Let's now create the plotter object and bind the data to it:

.. code-block:: cpp

  auto pcolorPlot = new omdi::PcolorPlot {
    { { "zfunc", new omdi::GridXY { xs, ys, nx, ny, zs } } },
    "PcolorExample"
  };

Because the ``PcolorPlot`` has to know the data layout, we need to wrap the raw data pointers inside a special ``omdi::GridXY`` container. Now we can simply call the plotter's ``plot()`` method inside the render loop to display the plot:

.. code-block:: cpp
  :emphasize-lines: 3

  app.Render(&state, [&]() {
    // ...
    pcolorPlot->plot();
  }, components, managers);


To see how performant the plotter is, let's add a timer object to keep track of the number of frames rendered per second. At the top of the ``main`` function, add the following:

.. code-block:: cpp

   auto timer = omdi::utils::Timer();

While we're there, let's also initialize the built-in logger which adds color-coded messages for different log-levels:

.. code-block:: cpp

   omdi::logger::Init();

At the end of your render loop, add the following code to compute and display the FPS, and update the timer:

.. code-block:: cpp
  :emphasize-lines: 5-6

  app.Render(&state, [&]() {
    // ...
    pcolorPlot->plot();

    omdi::logger::Log("FPS: %.3f", 1.0f / timer.delta());
    timer.tick();
  }, components, managers);


Finally, let's make the plot a bit more interesting by updating the ``z`` values every frame based on the elapsed time. Add the following code at the end of the render loop:

.. code-block:: cpp

  for (auto j = 0u; j < ny; ++j) {
    for (auto i = 0u; i < nx; ++i) {
      auto x         = xs[i];
      auto y         = ys[j];
      zs[j * nx + i] = zfunc(x, y, timer.elapsed());
    }
  }


More things to try
-------------------


