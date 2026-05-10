.. _omdi-pcolor-plot:

PcolorPlot
==========

Overview
--------

.. cpp:class:: omdi::PcolorPlot : public omdi::Plot, public omdi::plots::DataPlot<omdi::GridXY>

   Class for creating 2D heatmap (pseudocolor) plots.

   The :cpp:class:`omdi::PcolorPlot` class renders 2D scalar fields
   (e.g. :cpp:struct:`omdi::GridXY`) as pseudocolor heatmaps using
   ImPlot. It supports:

   - GPU-accelerated heatmap rendering for interactive performance,
   - an accompanying colorbar to visualize data ranges,
   - configurable aspect ratio (equal or free),
   - per-series visual customization via :cpp:class:`ImPlotSpec`,
   - selection of colormap via :cpp:enum:`ImPlotColormap`.

   Multiple named datasets can be registered; the active dataset is
   selected via an internal index. Datasets are stored **by value** inside
   the inherited :cpp:class:`omdi::plots::DataPlot\<omdi::GridXY\>` base,
   so no external data lifetime management is required.

Usage example
-------------

Basic usage with a single grid:

.. code-block:: cpp

  // Create pcolor plot with just a label — no data yet
  auto pcolor = omdi::PcolorPlot { "Scalar Field" };

  // Add or replace all datasets at once
  pcolor.update_all({
    { "field", omdi::GridXY { xs, ys, nx, ny, zs } }
  });

  // Or construct with initial data directly:
  auto pcolor2 = omdi::PcolorPlot { "Scalar Field", {
    { "field", omdi::GridXY { xs, ys, nx, ny, zs } }
  }};

  // Inside your ImGui/ImPlot drawing code:
  pcolor.plot();


Data members
------------

.. cpp:member:: bool omdi::PcolorPlot::m_aspect_equal

   Flag controlling whether the plot uses an equal aspect ratio.

   When ``true``, the X and Y axes are scaled so that units are equal
   on both axes, preserving the geometric shape of the grid.

.. cpp:member:: int omdi::PcolorPlot::m_which

   Index of the currently selected dataset in the internal data map.

   This determines which grid is displayed when :cpp:func:`omdi::PcolorPlot::plot`
   is called.

.. cpp:member:: ImPlotColormap omdi::PcolorPlot::m_colormap

   Colormap used for the pseudocolor rendering.

   Defaults to :cpp:enumerator:`ImPlotColormap_Viridis`. Other ImPlot
   colormaps can be selected to change the visual appearance of the
   heatmap and colorbar.

Constructor
-----------

.. cpp:function:: omdi::PcolorPlot::PcolorPlot( \
                     const std::string& label = "PcolorPlot", \
                     const std::map<std::string, omdi::GridXY>& data = {}, \
                     bool aspect_equal = true)

   Construct a pseudocolor plot with an optional label and initial datasets.

   :param label: Plot label / title (used in ImPlot). Defaults to
                 ``"PcolorPlot"``.
   :param data: Map from dataset names to :cpp:struct:`omdi::GridXY` values.
                Data is copied into the plot on construction. Defaults to an
                empty map.
   :param aspect_equal: Whether to enforce equal aspect ratio for the axes
                        (defaults to ``true``).

Inherited from DataPlot<GridXY>
---------------------------------

The following methods are inherited from
:cpp:class:`omdi::plots::DataPlot\<omdi::GridXY\>` and can be called directly
on a :cpp:class:`omdi::PcolorPlot` instance.

.. cpp:function:: void omdi::PcolorPlot::update(const std::string& label, omdi::GridXY data)

   Replace or insert a single named grid dataset.

   :param label: Name of the dataset to update.
   :param data: New :cpp:struct:`omdi::GridXY` value (copied by value).

.. cpp:function:: void omdi::PcolorPlot::update_all(std::map<std::string, omdi::GridXY> new_data)

   Replace all datasets at once.

   :param new_data: Map of new datasets. Replaces the entire contents of the
                    internal data store.

.. cpp:function:: auto omdi::PcolorPlot::set_spec(const std::string& label, const ImPlotSpec& spec) -> void

   Set the per-series plot specification for a named dataset.

   :param label: Dataset label to associate the spec with.
   :param spec: :cpp:class:`ImPlotSpec` controlling the visual appearance of
                the series.

.. cpp:function:: auto omdi::PcolorPlot::get_spec(const std::string& label) const -> ImPlotSpec

   Get the per-series plot specification for a named dataset.

   :param label: Dataset label whose spec to retrieve.
   :returns: The :cpp:class:`ImPlotSpec` associated with ``label``.

Plotting
--------

.. cpp:function:: void omdi::PcolorPlot::plot() override

   Render the pseudocolor plot.

   This method overrides :cpp:func:`omdi::Plot::plot` and:

   - selects the active :cpp:struct:`omdi::GridXY` dataset based on
     :cpp:member:`omdi::PcolorPlot::m_which`,
   - uses ImPlot's GPU-accelerated heatmap rendering to draw the 2D field,
   - applies the per-series :cpp:class:`ImPlotSpec` (retrieved via
     :cpp:func:`omdi::PcolorPlot::get_spec`) to control colormap and visual
     style for each series,
   - displays a colorbar indicating the data range and colormap,
   - respects the aspect ratio setting given by
     :cpp:member:`omdi::PcolorPlot::m_aspect_equal`,
   - applies the colormap specified by
     :cpp:member:`omdi::PcolorPlot::m_colormap`.

   It is typically called inside an ImGui/ImPlot context, for example
   within a window where plotting is performed.

Notes
-----

- :cpp:class:`omdi::PcolorPlot` **owns** all dataset copies; no external
  :cpp:struct:`omdi::GridXY` instances need to remain alive.
- The actual GPU-accelerated heatmap rendering and colorbar are provided
  by ImPlot; :cpp:class:`omdi::PcolorPlot` acts as a small adapter between
  your grid data (:cpp:struct:`omdi::GridXY`) and ImPlot's plotting API.
- Use :cpp:func:`omdi::PcolorPlot::update` to refresh a single series and
  :cpp:func:`omdi::PcolorPlot::update_all` to replace all series at once,
  for example when integrating with a simulation or background thread.
