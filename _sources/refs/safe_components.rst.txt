.. _omdi-component:

Component
=========

.. cpp:function:: void omdi::Component( \
                     const std::function<bool()>& opener, \
                     const std::function<void()>& item, \
                     const std::function<void()>& closer, \
                     omdi::ToastManager* toastManager)

   Helper for safely rendering an ImGui component with open/close logic.

   The :cpp:func:`omdi::Component` function wraps a typical ImGui component
   pattern (e.g. windows, child regions, tree nodes) consisting of:

   - an *opener* that begins a UI block and returns whether it is open,
   - an *item* body that renders the actual content,
   - a *closer* that ends the UI block.

   Any exceptions thrown from *item* are handled by
   :cpp:func:`omdi::safe::Render`, which logs the error via
   :cpp:class:`omdi::logger` and optionally shows an error toast using
   :cpp:class:`omdi::ToastManager`.

   :param opener: Callable that begins the component and returns ``true``
                  if the component should be rendered (e.g. an ImGui
                  `Begin*` function wrapped in a lambda).
   :param item: Callable that renders the body of the component.
   :param closer: Callable that closes/ends the component (e.g. the matching
                  `End*` function for the opener).
   :param toastManager: Optional pointer to :cpp:class:`omdi::ToastManager`.
                        If non-null, exceptions from *item* result in an
                        error toast in addition to logging.

   **Behavior:**

   - Calls ``opener()``.
   - If it returns ``true``:

     - calls :cpp:func:`omdi::safe::Render` to execute
       the body with exception handling,
     - then calls ``closer()`` to properly close the UI block.

   If ``opener()`` returns ``false``, neither *item* nor *closer* is called.


Usage example
-------------

Basic usage with an ``ImGui`` menu component and a :cpp:class:`omdi::Menubar`:

.. code-block:: cpp

    menubar.AddLeft([&]() {
      omdi::Component(
        []() {
          return ImGui::BeginMenu("Demo");
        },
        [&]() {
          ImGui::Checkbox("Show ImGui demo", &state.get<bool>("show_imgui_demo"));
          ImGui::Checkbox("Show ImPlot demo", &state.get<bool>("show_implot_demo"));
        },
        []() {
          ImGui::EndMenu();
        },
        &toastManager);
    });
