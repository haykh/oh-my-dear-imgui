.. _omdi-menubar:

Menubar
=======

Overview
--------

.. cpp:class:: omdi::Menubar

   Top menubar component for omdi applications.

   The :cpp:class:`omdi::Menubar` class manages a main menu bar at the top
   of the application window using ImGui. It supports three alignment zones:

   - **left**: typically for application menus (File, Edit, View, …),
   - **center**: for status or mode selectors,
   - **right**: for utility items (profile, settings, help, etc.).

   Each menu item is represented as a :cpp:struct:`omdi::MenuItem` holding
   a render callback (`std::function<void()>`). Rendering is performed
   inside :cpp:func:`omdi::Menubar::render`, which also integrates with
   :cpp:func:`omdi::safe::Render` to catch exceptions and optionally
   show error toasts via :cpp:class:`omdi::ToastManager`.

For example usage, see the :ref:`getting started guide <getting-started>`.

Related types
-------------

.. cpp:struct:: omdi::MenuItem

   Small helper struct storing a single menu item render callback.

   .. cpp:member:: std::function<void()> omdi::MenuItem::render

      Callable used to render the menu item (e.g. ImGui menu entries).

Public interface
----------------

.. cpp:function:: void omdi::Menubar::AddLeft(const std::function<void()>& item)

   Add a menu item to the left-aligned section of the menubar.

   :param item: Render callback for the item. Typically this lambda will
                contain ImGui menu code, such as calls to
                :cpp:func:`ImGui::BeginMenu` / :cpp:func:`ImGui::MenuItem`
                or a wrapper like ``SafeMenu``.

   Items are rendered in the order they are added.

.. cpp:function:: void omdi::Menubar::AddCenter(const std::function<void()>& item)

   Add a menu item to the center-aligned section of the menubar.

   :param item: Render callback for the item.

   The menubar computes the total width of center items and places them
   so they appear centered within the available menu bar width.

.. cpp:function:: void omdi::Menubar::AddRight(const std::function<void()>& item)

   Add a menu item to the right-aligned section of the menubar.

   :param item: Render callback for the item.

   Right-aligned items are rendered flush against the right edge of
   the menubar, taking into account their total width.

.. cpp:function:: void omdi::Menubar::render(omdi::ToastManager* toastManager = nullptr) const

   Render the menubar and all registered items.

   :param toastManager: Optional pointer to :cpp:class:`omdi::ToastManager`.
                        When provided, each item is executed via
                        :cpp:func:`omdi::safe::Render`, so exceptions
                        thrown inside item callbacks are logged and
                        can trigger error toasts.

   **Behavior:**

   - Begins the main menu bar with :cpp:func:`ImGui::BeginMainMenuBar`.
   - Renders left-aligned items in sequence, separated by ``SameLine``.
   - Measures the widths of center and right sections using an off-screen
     dummy window (via a private :cpp:func:`measureWidth` helper).
   - Positions and renders right-aligned items at the right edge.
   - Positions and renders center-aligned items so they are visually centered.
   - Ends the menu bar with :cpp:func:`ImGui::EndMainMenuBar`.

   All per-item render callbacks are invoked within an ImGui context and may
   use functions like :cpp:func:`ImGui::BeginMenu`,
   :cpp:func:`ImGui::MenuItem`, or custom wrappers such as ``SafeMenu``.

Notes
-----

- :cpp:class:`omdi::Menubar` does not own the ImGui context; it assumes
  ImGui has been initialized and a frame is in progress.
- For robust error handling, it is recommended to pass a valid
  :cpp:class:`omdi::ToastManager` pointer to
  :cpp:func:`omdi::Menubar::render`, so exceptions thrown by menu item
  callbacks result in logged errors and visual feedback to the user.
- Width measurement uses a hidden dummy window positioned off-screen to
  let ImGui compute the layout of center and right sections without
  affecting the visible UI.
