.. _omdi-toast-manager:

ToastManager
============

Overview
--------

.. cpp:class:: omdi::ToastManager

   Manager class for handling toast notifications.

   The :cpp:class:`omdi::ToastManager` class maintains a list of active
   toast notifications (small, transient popups) and is responsible for:

   - creating toasts of various types (success, warning, error, info),
   - limiting the number of rendered toasts,
   - positioning and spacing notifications on screen,
   - driving their life cycle (fade-in, wait, fade-out, expire) via
     per-toast state,
   - rendering them in the ImGui/ImDraw list.

   Notifications are represented internally by :cpp:class:`omdi::Toast`
   objects and use :cpp:enum:`omdi::toasts::Type` for severity/category,
   :cpp:enum:`omdi::toasts::Phase` for animation stage, and optional
   button callbacks for interactive actions.

Usage example
---------------

Basic usage in a UI:

.. code-block:: cpp

  auto toastManager = omdi::ToastManager();

  // somewhere in your UI code
  if (operation_successful) {
    toastManager.Add(omdi::toasts::Type::Success, "Operation completed successfully.");
  } else {
    toastManager.Add(omdi::toasts::Type::Error, "Operation failed. Please try again.");
  }

  // don't forget to add to a list of managers
  auto managers = omdi::managers_t{
    { "toast_manager", &toastManager },
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

.. cpp:member:: std::vector<std::unique_ptr<omdi::Toast>> omdi::ToastManager::m_toasts

   Collection of active toast notifications.

   Each element is a :cpp:class:`std::unique_ptr` owning a single
   :cpp:class:`omdi::Toast` instance. Toasts are created by the various
   :cpp:func:`omdi::ToastManager::Add` overloads and removed as they
   expire or are closed.

Constants
---------

.. cpp:member:: static constexpr unsigned int omdi::ToastManager::RENDER_LIMIT

   Maximum number of toasts to render at once.

   Toasts exceeding this limit may be skipped or postponed depending on
   the rendering strategy. This prevents the UI from being overwhelmed
   by too many notifications at once.

.. cpp:member:: static constexpr float omdi::ToastManager::NOTIFY_PADDING_X

   Horizontal padding from the screen edge to the first toast.

.. cpp:member:: static constexpr float omdi::ToastManager::NOTIFY_PADDING_Y

   Vertical padding from the screen edge to the first toast.

.. cpp:member:: static constexpr float omdi::ToastManager::NOTIFY_PADDING_MESSAGE_Y

   Vertical spacing between consecutive toast notifications.

Public interface
----------------

.. cpp:function:: void omdi::ToastManager::Add( \
                     const omdi::toasts::Type& type, \
                     unsigned int dismiss_time = omdi::Toast::NOTIFY_DEFAULT_DISMISS)

   Add a new toast notification of the given *type* with an optional
   auto-dismiss time.

   :param type: Notification type (e.g. :cpp:enum:`omdi::toasts::Type::Success`,
                :cpp:enum:`omdi::toasts::Type::Warning`,
                :cpp:enum:`omdi::toasts::Type::Error`,
                :cpp:enum:`omdi::toasts::Type::Info`).
   :param dismiss_time: Auto-dismiss time in milliseconds. If set to zero
                        (commonly used for errors), the toast will not auto-dismiss
                        and must be closed manually.

   Creates a toast with default title and content derived from *type*
   (e.g. “Success”, “Warning”, etc.).

.. cpp:function:: void omdi::ToastManager::Add( \
                     const omdi::toasts::Type& type, \
                     unsigned int dismiss_time, \
                     const std::string& content)

   Add a toast with a custom content message and explicit dismiss time.

   :param type: Notification type.
   :param dismiss_time: Auto-dismiss time in milliseconds.
   :param content: Text content/body of the toast.

   The title is typically derived from *type* (e.g. “Error”), while the
   message body is taken from *content*.

.. cpp:function:: void omdi::ToastManager::Add( \
                     const omdi::toasts::Type& type, \
                     const std::string& content)

   Add a toast with a custom content message and default dismiss time.

   :param type: Notification type.
   :param content: Text content/body of the toast.

   Uses :cpp:member:`omdi::Toast::NOTIFY_DEFAULT_DISMISS` as the dismiss time.

.. cpp:function:: void omdi::ToastManager::Add( \
                     const omdi::toasts::Type& type, \
                     unsigned int dismiss_time, \
                     const std::string& title, \
                     const std::string& button_label, \
                     const std::function<void()>& button_callback)

   Add a toast with custom title, content button, and callback.

   :param type: Notification type.
   :param dismiss_time: Auto-dismiss time in milliseconds.
   :param title: Custom title text for the toast.
   :param button_label: Label for the optional action button.
   :param button_callback: Callback function invoked when the button is pressed.

   This overload is used for interactive notifications, allowing the
   user to trigger an action (e.g. “Open folder”, “Retry”, “View details”)
   directly from the toast.

.. cpp:function:: void omdi::ToastManager::render()

   Render all active toast notifications.

   This function should be called once per frame from the main ImGui
   rendering loop. It:

   - determines the screen position and stacking of each toast using
     :cpp:member:`omdi::ToastManager::NOTIFY_PADDING_X`,
     :cpp:member:`omdi::ToastManager::NOTIFY_PADDING_Y`, and
     :cpp:member:`omdi::ToastManager::NOTIFY_PADDING_MESSAGE_Y`,
   - iterates over up to :cpp:member:`omdi::ToastManager::RENDER_LIMIT`
     active toasts,
   - queries each toast for its current fade phase and opacity,
   - draws the toast window, icon, title, content, and optional button,
   - removes toasts that have expired or been closed.

   The exact position (top/bottom, center/left/right) may be derived from
   a separate configuration using :cpp:enum:`omdi::toasts::Pos`.

Notes
-----

- :cpp:class:`omdi::ToastManager` owns all toast instances and is responsible
  for cleaning them up when they expire or are closed.
- For typical usage, you create a single global or per-application
  :cpp:class:`omdi::ToastManager` and call :cpp:func:`omdi::ToastManager::render`
  once per frame after setting up your main ImGui windows.
- Different toast types (:cpp:enum:`omdi::toasts::Type`) may be rendered
  with different colors, icons (e.g. Font Awesome symbols), and default
  titles to communicate severity clearly to the user.
