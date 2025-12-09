.. _omdi-scatter-plot:

ScatterPlot
===========

Overview
--------

.. cpp:class:: omdi::ScatterPlot : public omdi::Plot

   Class for creating 2D scatter plots.

   The :cpp:class:`omdi::ScatterPlot` class draws collections of scattered
   2D points (e.g. :cpp:struct:`omdi::Points`) using ImPlot. It supports:

   - plotting one or more named point datasets,
   - an option to enforce equal aspect ratio for X and Y axes,
   - reuse of the common :cpp:class:`omdi::Plot` interface.

   Datasets are stored as a map from string names to non-owning pointers to
   :cpp:struct:`omdi::Points`, allowing you to share point data across
   multiple plots without copying.


Usage example
-------------

Basic usage with two point sets:

.. code-block:: cpp 

  // Assume pts1 and pts2 are existing omdi::Points
  auto scatter = omdi::ScatterPlot({
    {"set A", &pts1},
    {"set B", &pts2}
  }, "Scatter Example", /*aspect_equal=*/true);

  // Inside your ImGui/ImPlot drawing code:
  scatter.plot();


Data members
------------

.. cpp:member:: bool omdi::ScatterPlot::m_aspect_equal

   Flag controlling whether the plot uses an equal aspect ratio.

   When ``true``, the X and Y axes are scaled so that one unit in X matches
   one unit in Y, which is useful for geometric or spatial data. When
   ``false``, the aspect ratio is free.

.. cpp:member:: std::map<std::string, const omdi::Points* const> omdi::ScatterPlot::m_data

   Map of named point sets to display.

   The keys are dataset names (e.g. ``"points_a"``, ``"points_b"``), and
   the values are non-owning pointers to :cpp:struct:`omdi::Points`
   instances representing scattered points.

Constructor
-----------

.. cpp:function:: omdi::ScatterPlot::ScatterPlot( \
                     const std::map<std::string, const omdi::Points* const>& data, \
                     const std::string& label = "ScatterPlot", \
                     bool aspect_equal = true)

   Construct a scatter plot from a set of point datasets.

   :param data: Map from dataset names to non-owning pointers to
                :cpp:struct:`omdi::Points` structures.
   :param label: Plot label / title (used in ImPlot).
   :param aspect_equal: Whether to enforce equal aspect ratio for the axes
                        (defaults to ``true``).

   The :cpp:class:`omdi::ScatterPlot` does not take ownership of the
   :cpp:struct:`omdi::Points` instances; the caller must ensure that
   the underlying point data outlives the plot.

Plotting
--------

.. cpp:function:: void omdi::ScatterPlot::plot() override

   Render the scatter plot.

   This method overrides :cpp:func:`omdi::Plot::plot` and:

   - iterates over the entries in :cpp:member:`omdi::ScatterPlot::m_data`,
   - for each dataset, retrieves the X/Y arrays and point count from the
     corresponding :cpp:struct:`omdi::Points`,
   - draws the points using ImPlot's scatter/marker primitives,
   - applies equal aspect ratio if
     :cpp:member:`omdi::ScatterPlot::m_aspect_equal` is ``true``.

   It is typically called inside an ImGui/ImPlot plotting context.

Notes
-----

- :cpp:class:`omdi::ScatterPlot` assumes that all :cpp:struct:`omdi::Points`
  instances in :cpp:member:`omdi::ScatterPlot::m_data` remain valid while
  the plot is being used.
- Enabling equal aspect ratio is recommended for spatial data where Euclidean
  distances and angles should not be visually distorted.
