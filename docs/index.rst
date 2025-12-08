.. include:: defs.rst

``oh-my-dear-imgui``
===================================

.. admonition:: :medium:`A bit more than minimal wrapper library for ImGui-based applications.`
  :class: important

  The idea behind ``oh-my-dear-imgui`` (``omdi``) is to provide an easily extensible and wrapper around the great Dear ImGui library. ``omdi`` wraps Dear ImGui, together with several other useful extensions exposing a more idiomatic and higher-level API to build ImGui-based applications in C++.


Features
--------

- basic manager classes for picker dialogs, toasts (notifications), screenshots, fonts, etc.;
- basic ui component classes, e.g., menubars, etc.;
- app state with optional conversion to/from toml;
- functionality for error handling (safe rendering + error notification) at runtime;
- external font/icon support (see ``src/assets/``);
- dependencies can be built from the downloaded submodules or fetched with ``CMake`` at compile time;
- includes some third-party ``ImGui`` plugins (also built in-tree): ``ImPlot``, ``ImGuiFileDialog``;
- includes GPU-accelerated version of ``ImPlot``-s ``PlotHeatmap`` (courtesy of unmerged |backendsbranch|_).

.. |backendsbranch| replace:: ``backends`` branch
.. _backendsbranch: https://github.com/epezent/implot/tree/backends


TODO
----

|check| documentation

|check| notifications (via `ImGuiNotify <https://github.com/TyomaVader/ImGuiNotify>`_)

|check| GPU-accelerated heatmap

|check| image export (via `stb <https://github.com/nothings/stb>`_)

|uncheck| support for other backends


.. toctree::
  :maxdepth: 1
  :hidden:

  Home <self>
  install
  getting-started