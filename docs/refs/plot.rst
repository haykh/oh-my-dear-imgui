.. _omdi-plot:

Plot
====

Overview
--------

.. cpp:class:: omdi::Plot

   Abstract base class for different types of plots.

   The :cpp:class:`omdi::Plot` class defines a minimal interface for
   plotting objects in the ``omdi`` framework. Concrete plot types
   such as :cpp:class:`omdi::ScatterPlot` and :cpp:class:`omdi::PcolorPlot`
   derive from this base class and implement the pure virtual
   :cpp:func:`omdi::Plot::plot` method.

   Each plot has a string label that can be used as a title or identifier
   in ImGui/ImPlot contexts.

Data members
------------

.. cpp:member:: std::string omdi::Plot::m_label

   Label used to identify the plot (e.g. as a title in ImPlot).

   Defaults to ``"GenericPlot"`` if no label is provided to the constructor.

Constructor
-----------

.. cpp:function:: omdi::Plot::Plot(const std::string& label = "GenericPlot")

   Construct a plot with the given label.

   :param label: Human-readable label for the plot (default: ``"GenericPlot"``).

Public interface
----------------

.. cpp:function:: virtual void omdi::Plot::plot() = 0

   Pure virtual function that renders the plot.

   Concrete subclasses must implement this method to perform the actual
   drawing using ImGui/ImPlot or other rendering backends.

.. cpp:function:: const std::string& omdi::Plot::label() const

   Get the label associated with the plot.

   :returns: Constant reference to the internal label string.

DataPlot<T>
-----------

.. cpp:class:: template <typename T> omdi::plots::DataPlot

   Base class template for plots that own their data.

   :cpp:class:`omdi::plots::DataPlot` provides data storage and management
   for concrete plot types such as :cpp:class:`omdi::ScatterPlot` and
   :cpp:class:`omdi::PcolorPlot`. It holds a named map of datasets of type
   ``T`` and a corresponding map of per-series plot specifications
   (:cpp:class:`ImPlotSpec`).

   Concrete plot classes inherit from both :cpp:class:`omdi::Plot` and
   ``DataPlot<T>``, gaining the rendering interface from the former and the
   data management interface from the latter.

Data members
~~~~~~~~~~~~

.. cpp:member:: std::map<std::string, T> omdi::plots::DataPlot::m_data

   Map of named datasets owned by the plot.

   Keys are user-assigned dataset labels; values are data objects of type ``T``
   (e.g., :cpp:struct:`omdi::Points` or :cpp:struct:`omdi::GridXY`).

.. cpp:member:: std::map<std::string, ImPlotSpec> omdi::plots::DataPlot::m_specs

   Map of per-series plot specifications.

   Each entry associates a dataset label with an :cpp:class:`ImPlotSpec` that
   controls how the corresponding series is rendered (e.g., colormap, line
   style).

Constructor
~~~~~~~~~~~

.. cpp:function:: template <typename T> \
                  omdi::plots::DataPlot<T>::DataPlot( \
                    const std::map<std::string, T>& data = {})

   Construct a ``DataPlot`` with an optional initial set of named datasets.

   :param data: Map of initial datasets (default: empty). Each entry is
                copied into :cpp:member:`omdi::plots::DataPlot::m_data`.

Public interface
~~~~~~~~~~~~~~~~

.. cpp:function:: template <typename T> \
                  void omdi::plots::DataPlot<T>::update( \
                    const std::string& label, T data)

   Replace or insert a single named dataset.

   :param label: Name of the dataset to update.
   :param data: New data value (copied by value).

   If a dataset with the given label already exists it is replaced; otherwise
   a new entry is created.

.. cpp:function:: template <typename T> \
                  void omdi::plots::DataPlot<T>::update_all( \
                    std::map<std::string, T> new_data)

   Replace all datasets at once.

   :param new_data: Map of new datasets. Replaces the entire contents of
                    :cpp:member:`omdi::plots::DataPlot::m_data`.

.. cpp:function:: template <typename T> \
                  auto omdi::plots::DataPlot<T>::set_spec( \
                    const std::string& label, const ImPlotSpec& spec) -> void

   Set the plot specification for a named series.

   :param label: Dataset label to associate the spec with.
   :param spec: :cpp:class:`ImPlotSpec` controlling the visual appearance of
                the series.

.. cpp:function:: template <typename T> \
                  auto omdi::plots::DataPlot<T>::get_spec( \
                    const std::string& label) const -> ImPlotSpec

   Get the plot specification for a named series.

   :param label: Dataset label whose spec to retrieve.
   :returns: The :cpp:class:`ImPlotSpec` associated with ``label``.
