.. _omdi-font-manager:

FontManager
===========

.. cpp:namespace:: omdi

Overview
--------

.. cpp:class:: FontManager

   Font manager for handling multiple fonts and sizes in ImGui.

   The :cpp:class:`omdi::FontManager` class manages a set of ImGui fonts
   (and optional icon fonts) grouped by name and size. It provides:

   - Registration of fonts from memory or from files.
   - A fixed set of logical sizes (e.g. Small, Normal, Medium, Large, Huge).
   - Access to fonts and icon fonts by name and size.
   - Tracking of the currently active font and size.
   - Helper functions to build and clear the ImGui font atlas.

   Internally, it uses maps from font names to size-specific :cpp:class:`ImFont`
   pointers, and integrates with :cpp:class:`ImGuiIO` for font configuration.

   The available sizes are stored in :cpp:member:`omdi::FontManager::SIZES`,
   which typically contains ``Small``, ``Normal``, ``Medium``, ``Large``,
   and ``Huge``.

Usage example
-------------

Basic usage:

.. code-block:: cpp

  auto fontManager = omdi::FontManager();
  auto managers = omdi::managers_t {
    { "font_manager", &fontManager },
    // ... other managers
  };

  app.Init(&state, managers);
  app.Render(&state, [&]() {
    // render callback
  },
  components,
  managers);


Advanced usage to load custom fonts:

.. code-block:: cpp

  auto fontManager = omdi::FontManager();

  // add from a ttf file
  fontManager.add(&ImGui::GetIO(), "CustomFont", omdi::fonts::Normal, "path/to/font.ttf", nullptr);
  fontManager.build(&ImGui::GetIO());

  // size_index = 2 corresponds to 'Normal' (16px)
  fontManager.setActiveFont(&ImGui::GetIO(), /*font_index=*/0, /*size_index=*/2);


Public interface
----------------

Sizes and active font state
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:member:: std::vector<Size> FontManager::SIZES

   List of supported font sizes.

   Typically contains logical size values such as ``Small``, ``Normal``,
   ``Medium``, ``Large``, and ``Huge``. The exact :cpp:enum:`Size` values
   are determined by your application.

.. cpp:function:: std::string FontManager::active_font() const

   Get the name of the currently active font.

   :returns: Name of the active font, or an empty string if none is active.

.. cpp:function:: int FontManager::active_font_idx() const

   Get the index of the currently active font in the internal font list.

   :returns: Zero-based index of the active font, or ``-1`` if none is active.

.. cpp:function:: Size FontManager::active_font_size() const

   Get the currently active font size.

   :returns: The active :cpp:enum:`Size` value, or ``Size::None`` if no size
             is active.

Font and icon access
~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: ImFont* FontManager::font(const std::string& name, Size size)

   Retrieve a font by name and size.

   :param name: Font family/name identifier (e.g. ``"Roboto"``).
   :param size: Logical size (e.g. :cpp:enum:`Size::Normal`).
   :returns: Pointer to the corresponding :cpp:class:`ImFont`, or ``nullptr``
             if the font/size combination is not available.

.. cpp:function:: ImFont* FontManager::icon(const std::string& name, Size size)

   Retrieve an icon font by name and size.

   :param name: Icon font identifier (e.g. ``"FontAwesome"`` or similar).
   :param size: Logical size.
   :returns: Pointer to the corresponding :cpp:class:`ImFont` used for icons,
             or ``nullptr`` if not available.

.. cpp:function:: std::vector<const char*> FontManager::fontnames() const

   Get a list of available font names.

   :returns: A vector of C-string pointers, each representing a font name.
             The lifetime of these strings is tied to the
             :cpp:class:`omdi::FontManager` instance.

Initialization and configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: void FontManager::initFonts(ImGuiIO* io)

   Initialize font-related data using the given ImGui IO object.

   :param io: Pointer to :cpp:class:`ImGuiIO` used by the current ImGui context.

   This function typically prepares internal structures and may configure
   default fonts or font settings before fonts are added.

.. cpp:function:: void FontManager::setActiveFont(ImGuiIO* io, int font_index, int size_index)

   Set the active font and size, and update ImGui to use them.

   :param io: Pointer to :cpp:class:`ImGuiIO` for the current ImGui context.
   :param font_index: Index into the internal font list (e.g. as returned by
                      :cpp:func:`omdi::FontManager::fontnames`).
   :param size_index: Index into :cpp:member:`omdi::FontManager::SIZES`.

   This function updates :cpp:func:`ImGui::GetFont` / ImGui style to use the
   selected font/size combination as the main UI font.

Managing the font atlas
~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: void FontManager::clear(ImGuiIO* io) const

   Clear fonts from the ImGui IO font atlas.

   :param io: Pointer to :cpp:class:`ImGuiIO`.

   Clears font data from the ImGui font atlas. Typically used before
   rebuilding or reconfiguring fonts.

.. cpp:function:: void FontManager::build(ImGuiIO* io) const

   Build the ImGui font atlas after fonts have been added.

   :param io: Pointer to :cpp:class:`ImGuiIO`.

   This calls the underlying ImGui font-building routines to bake the
   registered fonts into a texture atlas. Must be called after all
   desired fonts are added, and before rendering with them.

Adding fonts
~~~~~~~~~~~~

.. cpp:function:: void FontManager::add(ImGuiIO* io, \
                                        const std::string& name, \
                                        Size size, \
                                        const void* data, \
                                        int data_size, \
                                        const ImWchar* glyph_ranges = nullptr)

   Add a font from in-memory data.

   :param io: Pointer to :cpp:class:`ImGuiIO`.
   :param name: Font name identifier (e.g. ``"Roboto"``).
   :param size: Logical font size.
   :param data: Pointer to the font data (e.g. TTF bytes in memory).
   :param data_size: Size of *data* in bytes.
   :param glyph_ranges: Optional ImGui glyph range (see ImGui font API).
   :returns: (none)

   Use this to load fonts that are bundled directly in your binary or loaded
   into memory by other means.

.. cpp:function:: void FontManager::add(ImGuiIO* io, \
                                        const std::string& name, \
                                        Size size, \
                                        const std::string& filename, \
                                        const ImWchar* glyph_ranges = nullptr)

   Add a font from a file.

   :param io: Pointer to :cpp:class:`ImGuiIO`.
   :param name: Font name identifier.
   :param size: Logical font size.
   :param filename: Path to the font file (e.g. TTF/OTF).
   :param glyph_ranges: Optional ImGui glyph range.
   :returns: (none)

   This overload loads font data from disk and registers it under the given
   *name* and *size*.

Notes
-----

- :cpp:class:`omdi::FontManager` does not own the :cpp:class:`ImGuiIO` object;
  it only uses it to configure fonts and build the font atlas.
- After adding or changing fonts via :cpp:func:`omdi::FontManager::add`, you
  should call :cpp:func:`omdi::FontManager::build` to rebuild the atlas.
- The :cpp:enum:`Size` type is assumed to be defined elsewhere (e.g. in the
  same namespace) with values such as ``Small``, ``Normal``, ``Medium``,
  ``Large``, ``Huge``, and ``None``.
