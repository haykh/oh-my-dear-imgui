.. _omdi-scatter-plot:

ScatterPlot
===========

Overview
--------

.. cpp:class:: omdi::ScatterPlot : public omdi::Plot, public omdi::plots::DataPlot<omdi::Points>

   Class for creating 2D scatter plots.

   The :cpp:class:`omdi::ScatterPlot` class draws collections of scattered
   2D points (e.g. :cpp:struct:`omdi::Points`) using ImPlot. It supports:

   - plotting one or more named point datasets,
   - an option to enforce equal aspect ratio for X and Y axes,
   - per-series visual customization via :cpp:class:`ImPlotSpec`,
   - reuse of the common :cpp:class:`omdi::Plot` interface.

   Datasets are stored **by value** inside the inherited
   :cpp:class:`omdi::plots::DataPlot\<omdi::Points\>` base, so no external
   data lifetime management is required.


Usage example
-------------

Basic usage with two point sets:

.. code-block:: cpp

  // Create scatter plot with just a label — no data yet
  auto scatter = omdi::ScatterPlot { "Scatter Example" };

  // Add or replace all datasets at once
  scatter.update_all({
    { "set A", omdi::Points { {0.0f, 1.0f, 2.0f}, {1.0f, 0.5f, 0.25f}, 3 } },
    { "set B", omdi::Points { xs_vec, ys_vec, n } }
  });

  // Or construct with initial data directly:
  auto scatter2 = omdi::ScatterPlot { "Scatter Example", {
    { "set A", omdi::Points { xs_vec, ys_vec, n } }
  }};

  // Inside your ImGui/ImPlot drawing code:
  scatter.plot();


Data members
------------

.. cpp:member:: bool omdi::ScatterPlot::m_aspect_equal

   Flag controlling whether the plot uses an equal aspect ratio.

   When ``true``, the X and Y axes are scaled so that one unit in X matches
   one unit in Y, which is useful for geometric or spatial data. When
   ``false``, the aspect ratio is free.

Constructor
-----------

.. cpp:function:: omdi::ScatterPlot::ScatterPlot( \
                     const std::string& label = "ScatterPlot", \
                     const std::map<std::string, omdi::Points>& data = {}, \
                     bool aspect_equal = true)

   Construct a scatter plot with an optional label and initial datasets.

   :param label: Plot label / title (used in ImPlot). Defaults to
                 ``"ScatterPlot"``.
   :param data: Map from dataset names to :cpp:struct:`omdi::Points` values.
                Data is copied into the plot on construction. Defaults to an
                empty map.
   :param aspect_equal: Whether to enforce equal aspect ratio for the axes
                        (defaults to ``true``).

Inherited from DataPlot<Points>
---------------------------------

The following methods are inherited from
:cpp:class:`omdi::plots::DataPlot\<omdi::Points\>` and can be called directly
on a :cpp:class:`omdi::ScatterPlot` instance.

.. cpp:function:: void omdi::ScatterPlot::update(const std::string& label, omdi::Points data)

   Replace or insert a single named point dataset.

   :param label: Name of the dataset to update.
   :param data: New :cpp:struct:`omdi::Points` value (copied by value).

.. cpp:function:: void omdi::ScatterPlot::update_all(std::map<std::string, omdi::Points> new_data)

   Replace all datasets at once.

   :param new_data: Map of new datasets. Replaces the entire contents of the
                    internal data store.

.. cpp:function:: auto omdi::ScatterPlot::set_spec(const std::string& label, const ImPlotSpec& spec) -> void

   Set the per-series plot specification for a named dataset.

   :param label: Dataset label to associate the spec with.
   :param spec: :cpp:class:`ImPlotSpec` controlling the visual appearance of
                the series.

.. cpp:function:: auto omdi::ScatterPlot::get_spec(const std::string& label) const -> ImPlotSpec

   Get the per-series plot specification for a named dataset.

   :param label: Dataset label whose spec to retrieve.
   :returns: The :cpp:class:`ImPlotSpec` associated with ``label``.

Plotting
--------

.. cpp:function:: void omdi::ScatterPlot::plot() override

   Render the scatter plot.

   This method overrides :cpp:func:`omdi::Plot::plot` and:

   - iterates over the entries in the internal data map,
   - for each dataset, retrieves the X/Y arrays and point count from the
     corresponding :cpp:struct:`omdi::Points`,
   - applies the per-series :cpp:class:`ImPlotSpec` (retrieved via
     :cpp:func:`omdi::ScatterPlot::get_spec`) to control visual style,
   - draws the points using ImPlot's scatter/marker primitives,
   - applies equal aspect ratio if
     :cpp:member:`omdi::ScatterPlot::m_aspect_equal` is ``true``.

   It is typically called inside an ImGui/ImPlot plotting context.

Notes
-----

- :cpp:class:`omdi::ScatterPlot` **owns** all dataset copies; no external
  :cpp:struct:`omdi::Points` instances need to remain alive.
- Enabling equal aspect ratio is recommended for spatial data where Euclidean
  distances and angles should not be visually distorted.
- Use :cpp:func:`omdi::ScatterPlot::update` to refresh a single series and
  :cpp:func:`omdi::ScatterPlot::update_all` to replace all series at once,
  for example when integrating with a simulation or background thread.
