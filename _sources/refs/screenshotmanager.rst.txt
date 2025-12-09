.. _omdi-screenshot-manager:

ScreenshotManager
=================

Overview
--------

.. cpp:class:: omdi::ScreenshotManager

   Manager for taking and saving screenshots of the application window.

   The :cpp:class:`omdi::ScreenshotManager` class provides a small helper
   for scheduling screenshots from within the render loop. It:

   - lets you request a screenshot with a configurable filename and path,
   - applies a short frame delay before capturing (to let the UI update),
   - uses stb-based image saving routines internally to write the framebuffer
     to disk,
   - can optionally notify the user via :cpp:class:`omdi::ToastManager`
     when the screenshot is processed.

   Screenshots are stored in a directory (default: ``"screenshots"``) with
   a chosen filename (default: ``"screenshot.png"``).


Usage example
-------------

Basic usage in a UI:

.. code-block:: cpp

  auto screenshotManager = omdi::ScreenshotManager();

  // somewhere in your UI code
  if (ImGui::Button("Save Image")) {
    screenshotManager.request(); // uses default filename and path
  }

  // don't forget to add to a list of managers
  auto managers = omdi::managers_t{
    {"screenshot_manager", &screenshotManager},
    // ...
  };

  app.Init(&state, managers);
  app.Render(&state, [&]() {
    // render loop
  },
  components,
  managers);


Data members
------------

.. cpp:member:: bool omdi::ScreenshotManager::m_screenshot_requested

   Flag indicating whether a screenshot has been requested and is waiting
   to be processed.

.. cpp:member:: unsigned int omdi::ScreenshotManager::m_delay

   Frame delay counter before capturing the screenshot.

   Typically initialized to a small positive value (e.g. ``5``) when a
   request is made, and decremented each frame in :cpp:func:`omdi::ScreenshotManager::process`
   until the capture occurs.

.. cpp:member:: std::filesystem::path omdi::ScreenshotManager::m_path

   Directory where screenshots will be saved.

   Defaults to ``"screenshots"``.

.. cpp:member:: std::filesystem::path omdi::ScreenshotManager::m_fname

   Filename for the next screenshot.

   Defaults to ``"screenshot.png"``.

Constructor
-----------

.. cpp:function:: omdi::ScreenshotManager::ScreenshotManager()

   Default-construct a screenshot manager.

   Initializes the manager with no pending screenshot request, a zero delay,
   default screenshot directory (``"screenshots"``), and default filename
   (``"screenshot.png"``).

Public interface
----------------

.. cpp:function:: void omdi::ScreenshotManager::request( \
                     const std::filesystem::path& fname = "screenshot.png", \
                     const std::filesystem::path& path = "screenshots")

   Request that a screenshot be taken.

   :param fname: Filename for the screenshot (default: ``"screenshot.png"``).
   :param path: Directory in which to save the screenshot
                (default: ``"screenshots"``).

   This function:

   - marks a screenshot as requested,
   - sets an internal delay (e.g. a few frames) before capturing,
   - stores the requested filename and directory.

   The actual capture and saving is performed later by
   :cpp:func:`omdi::ScreenshotManager::process`, which should be called
   from the render loop. Internally, stb-based routines are used to write
   the captured image to disk.

.. cpp:function:: void omdi::ScreenshotManager::process(omdi::ToastManager* toasts = nullptr)

   Process a pending screenshot request.

   :param toasts: Optional pointer to an :cpp:class:`omdi::ToastManager`
                  for displaying user notifications (e.g. success/failure).

   Typical behavior:

   - If no screenshot is requested, the function returns immediately.
   - If a screenshot is requested:

     - decrement the internal delay counter,
     - when the delay reaches zero, capture the current framebuffer,
     - save the image using stb-based saving functions to
       :cpp:member:`omdi::ScreenshotManager::m_path` /
       :cpp:member:`omdi::ScreenshotManager::m_fname`,
     - optionally show a toast notification (if *toasts* is non-null),
     - clear the request flag.

   This function is intended to be called once per frame from within the
   render loop.

.. cpp:function:: bool omdi::ScreenshotManager::processing() const

   Check whether a screenshot request is currently pending.

   :returns: ``true`` if a screenshot has been requested and not yet fully
             processed, ``false`` otherwise.

Notes
-----

- Screenshot capture uses stb-based image saving; ensure stb is linked and
  configured in your project.
- The directory specified by :cpp:member:`omdi::ScreenshotManager::m_path`
  must be writable and is not automatically created unless that behavior
  is implemented in the `process` function.
- The delay between :cpp:func:`omdi::ScreenshotManager::request` and the
  actual capture helps ensure the rendered frame reflects any UI state
  changes that triggered the screenshot.
