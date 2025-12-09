References
==========

.. toctree::
   :maxdepth: 1
   :hidden:
   :glob:

   refs/*

Core
--------------

:doc:`State <refs/state>`
~~~~~~~~~~~~~~~~~~~~~~~~~~
State manager for storing and retrieving application state variables.

:doc:`App <refs/app>`
~~~~~~~~~~~~~~~~~~~~~~~~~~
Main class for the ``omdi`` application. Handles the window instantiation, event loop, and overall application state.

Managers
----------

:doc:`FontManager <refs/fontmanager>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Font manager for handling multiple font families and sizes in ImGui. Supports dynamic loading and caching of fonts.

:doc:`PickerManager <refs/pickermanager>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Manager for handling file/directory picker dialogs.

:doc:`ScreenshotManager <refs/screenshotmanager>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Manager for taking and saving screenshots of the application window.

:doc:`ToastManager <refs/toastmanager>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Manager class for handling toast notifications.

Containers
-----------

:doc:`Points <refs/points>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Structure to hold 2D scattered points data.

:doc:`GridXY <refs/gridxy>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Structure to hold 2D grid data.

Plotter classes
----------------

:doc:`Plot <refs/plot>`
~~~~~~~~~~~~~~~~~~~~~~~~~~
Abstract base class for different types of plots.

:doc:`PcolorPlot <refs/pcolorplot>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Class for creating 2D heatmap (pseudocolor) plots.

:doc:`ScatterPlot <refs/scatterplot>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Class for creating 2D scatter plots.

Utilities
--------------

:doc:`Logger <refs/logger>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Simple logging utility using ``plog``.

:doc:`Timer <refs/timer>`
~~~~~~~~~~~~~~~~~~~~~~~~~~
Timer class for measuring elapsed time and frame delta time.

Examples
---------------

:doc:`2D field <refs/example_field_2d>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:doc:`Rotating pointcloud <refs/example_rotating_pointcloud>`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
