.. _omdi-pcolor-plot:

PcolorPlot
==========

Overview
--------

.. cpp:class:: omdi::PcolorPlot : public omdi::Plot

   Class for creating 2D heatmap (pseudocolor) plots.

   The :cpp:class:`omdi::PcolorPlot` class renders 2D scalar fields
   (e.g. :cpp:struct:`omdi::GridXY`) as pseudocolor heatmaps using
   ImPlot. It supports:

   - GPU-accelerated heatmap rendering for interactive performance,
   - an accompanying colorbar to visualize data ranges,
   - configurable aspect ratio (equal or free),
   - selection of colormap via :cpp:enum:`ImPlotColormap`.

   Multiple named datasets can be registered; the active dataset is
   selected via an internal index.

Usage example
-------------

Basic usage with a single grid:

.. code-block:: cpp

  // Assuming 'grid' is an existing omdi::GridXY
  auto pcolor = omdi::PcolorPlot({
    { "field", &grid }
  }, "Scalar Field", /*aspect_equal=*/true);

  // Inside your ImGui/ImPlot drawing code:
  pcolor.plot();


Data members
------------

.. cpp:member:: bool omdi::PcolorPlot::m_aspect_equal

   Flag controlling whether the plot uses an equal aspect ratio.

   When ``true``, the X and Y axes are scaled so that units are equal
   on both axes, preserving the geometric shape of the grid.

.. cpp:member:: int omdi::PcolorPlot::m_which

   Index of the currently selected dataset in :cpp:member:`omdi::PcolorPlot::m_data`.

   This determines which grid is displayed when :cpp:func:`omdi::PcolorPlot::plot`
   is called.

.. cpp:member:: ImPlotColormap omdi::PcolorPlot::m_colormap

   Colormap used for the pseudocolor rendering.

   Defaults to :cpp:enumerator:`ImPlotColormap_Viridis`. Other ImPlot
   colormaps can be selected to change the visual appearance of the
   heatmap and colorbar.

.. cpp:member:: std::map<std::string, const omdi::GridXY* const> omdi::PcolorPlot::m_data

   Map of named 2D grids to display.

   The keys are dataset names (e.g. ``"temperature"`` or ``"pressure"``),
   and the values are non-owning pointers to :cpp:struct:`omdi::GridXY`
   instances holding the grid coordinates and scalar values.

Constructor
-----------

.. cpp:function:: omdi::PcolorPlot::PcolorPlot( \
                     const std::map<std::string, const omdi::GridXY* const>& data, \
                     const std::string& label = "PcolorPlot", \
                     bool aspect_equal = true)

   Construct a pseudocolor plot from a set of 2D grids.

   :param data: Map from dataset names to non-owning pointers to
                :cpp:struct:`omdi::GridXY` structures.
   :param label: Plot label / title (used in ImPlot).
   :param aspect_equal: Whether to enforce equal aspect ratio for the axes
                        (defaults to ``true``).

   The :cpp:class:`omdi::PcolorPlot` does not take ownership of the
   :cpp:struct:`omdi::GridXY` instances; the caller must ensure that
   the underlying grid data outlives the plot.

Plotting
--------

.. cpp:function:: void omdi::PcolorPlot::plot() override

   Render the pseudocolor plot.

   This method overrides :cpp:func:`omdi::Plot::plot` and:

   - selects the active :cpp:struct:`omdi::GridXY` dataset based on
     :cpp:member:`omdi::PcolorPlot::m_which`,
   - uses ImPlot's GPU-accelerated heatmap rendering to draw the 2D field,
   - displays a colorbar indicating the data range and colormap,
   - respects the aspect ratio setting given by
     :cpp:member:`omdi::PcolorPlot::m_aspect_equal`,
   - applies the colormap specified by
     :cpp:member:`omdi::PcolorPlot::m_colormap`.

   It is typically called inside an ImGui/ImPlot context, for example
   within a window where plotting is performed.

Notes
-----

- The actual GPU-accelerated heatmap rendering and colorbar are provided
  by ImPlot; :cpp:class:`omdi::PcolorPlot` acts as a small adapter between
  your grid data (:cpp:struct:`omdi::GridXY`) and ImPlot’s plotting API.
- Make sure that the :cpp:struct:`omdi::GridXY` instances in
  :cpp:member:`omdi::PcolorPlot::m_data` remain valid for as long as
  the plot is used.
