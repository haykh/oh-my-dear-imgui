.. _omdi-picker-manager:

PickerManager
=============

Overview
--------

.. cpp:class:: omdi::PickerManager

   Manager for handling file/directory picker dialogs.

   The :cpp:class:`omdi::PickerManager` class maintains a collection of
   ImGuiFileDialog (:cpp:class:`IGFD::FileDialog`) instances along with
   per-dialog callbacks. It provides a simple interface to:

   - open file or directory pickers with customizable titles, prompts,
     initial paths, and file filters,
   - render and manage all active dialogs in the main UI loop,
   - invoke user-provided callbacks when a dialog is accepted,
   - automatically clean up dialogs when they are closed.

   Internally, dialogs are stored as pairs of:

   - :cpp:class:`std::unique_ptr<IGFD::FileDialog>`  
   - :cpp:type:`omdi::picker::callback_t` (a callback called on success)

   Logging is performed through :cpp:class:`omdi::logger` when dialogs
   are opened, accepted, cancelled, and removed.

Usage example
-------------

Basic usage as a file picker with a succest toast notification:

.. code-block:: cpp

  auto pickerDialogManager = omdi::PickerManager();
  auto toastManager        = omdi::ToastManager();

  // somewhere in the UI code:
  pickerDialogManager.Add([&](IGFD::FileDialog* dialog) {
    const auto fpath_name = dialog->GetFilePathName();
    const auto fpath      = dialog->GetCurrentPath();
    toastManager.Add(omdi::toasts::Type::Success,
                      omdi::fmt::format("picked %s %s",
                                        fpath_name.c_str(),
                                        fpath.c_str()));
  });

  // don't forget to pass it with other managers:
  auto managers = omdi::managers_t {
    {      "toast_manager",        &toastManager },
    {     "picker_manager", &pickerDialogManager }
    // ...
  };
  app.Init(&state, managers);
  app.Render(&state, [&]() {
    // render callback
    // ...
    // picker is handled automatically
  },
  components,
  managers);


Related types
-------------

.. cpp:namespace-push:: omdi::picker

.. cpp:type:: callback_t = std::function<void(IGFD::FileDialog*)>

   Callback type used by :cpp:class:`omdi::PickerManager`.

   The callback is invoked when the user accepts a dialog
   (i.e. when :cpp:func:`IGFD::FileDialog::IsOk` returns true) and receives
   a pointer to the corresponding :cpp:class:`IGFD::FileDialog` instance.

.. cpp:namespace-pop::

Public interface
----------------

.. cpp:function:: void omdi::PickerManager::Add( \
                     omdi::picker::callback_t callback, \
                     const std::string& title = "PickerDialog", \
                     const std::string& prompt = "Pick a file or directory", \
                     const std::string& path = ".", \
                     const char* filter = nullptr)

   Add a picker dialog to the manager.

   :param callback: Function to be called when the dialog is accepted
                    (``IsOk() == true``). The callback receives a pointer
                    to the :cpp:class:`IGFD::FileDialog` instance, which
                    can be queried for the selected file(s) or directory.
   :param title: Title of the dialog window (default: ``"PickerDialog"``).
   :param prompt: Prompt message shown in the dialog
                  (default: ``"Pick a file or directory"``).
   :param path: Initial path shown when the dialog opens (default: ``"."``).
   :param filter: File extension filter (default: ``nullptr``). If this is
                  ``nullptr``, the dialog behaves like a directory picker;
                  otherwise, it filters files according to the given pattern.

   This method:

   - constructs an :cpp:class:`IGFD::FileDialog`,
   - configures it with the supplied path, title, prompt, and filter via
     :cpp:func:`IGFD::FileDialog::OpenDialog`,
   - stores the dialog and callback in the internal list,
   - logs the operation via :cpp:class:`omdi::logger`
     (e.g. dialog opened, total dialog count).

.. cpp:function:: void omdi::PickerManager::render()

   Render and manage all active picker dialogs.

   This method should be called from the main ImGui rendering loop. For each
   active dialog, it:

   - configures file styles (e.g. special styling for ``.ttf`` files),
   - displays the dialog via :cpp:func:`IGFD::FileDialog::Display`,
   - checks whether the dialog has been accepted or cancelled:

     - if accepted (``IsOk() == true``):

       - logs success via :cpp:class:`omdi::logger`,
       - invokes the associated :cpp:type:`omdi::picker::callback_t`
         with the pointer to :cpp:class:`IGFD::FileDialog`,
       - closes the dialog and removes it from the manager;

     - if cancelled:

       - logs cancellation,
       - closes and removes the dialog from the manager.

   The method iterates over all managed dialogs and removes them once they
   are closed, ensuring no stale dialogs remain in the list.

Notes
-----

- :cpp:class:`omdi::PickerManager` does not own or manage the global ImGui
  or ImGuiFileDialog state beyond the dialogs it creates.
- All dialogs are non-blocking and rendered as part of the normal ImGui
  frame; :cpp:func:`omdi::PickerManager::render` must be called every frame
  while dialogs are active.
- The lifetime of the :cpp:class:`IGFD::FileDialog` passed into the callback
  is limited to the callback invocation and the remainder of the current
  frame; the dialog is removed from the manager immediately after handling
  OK/Cancel.
