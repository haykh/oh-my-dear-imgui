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
