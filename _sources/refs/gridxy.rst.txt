.. _omdi-grid-xy:

GridXY
======

.. cpp:namespace:: omdi

Overview
--------

.. cpp:struct:: GridXY

   Structure to hold 2D grid data.

   The :cpp:struct:`omdi::GridXY` struct stores and **owns** vectors for the X
   and Y coordinate axes of a regular 2D grid, along with the grid dimensions
   and a vector for the associated scalar data ``z``.

   Data is copied into the struct on construction, so the caller does not need
   to keep the source arrays alive after creating a :cpp:struct:`omdi::GridXY`
   instance.

Usage example
-------------

Basic usage with ``std::vector`` arrays:

.. code-block:: cpp

  constexpr size_t nx = 3;
  constexpr size_t ny = 2;

  auto xs = std::vector<float> { 0.0f, 1.0f, 2.0f };
  auto ys = std::vector<float> { 0.0f, 1.0f };
  auto zs = std::vector<float> {
      0.0f, 1.0f,
      2.0f, 3.0f,
      4.0f, 5.0f
  };

  auto grid = omdi::GridXY(xs, ys, nx, ny, zs);

  // grid owns its own copies of xs, ys, and zs.

Data members
------------

.. cpp:member:: std::vector<float> GridXY::x

   Vector of X coordinates.

   Typically contains :cpp:member:`omdi::GridXY::nx` monotonically increasing
   X coordinates.

.. cpp:member:: std::vector<float> GridXY::y

   Vector of Y coordinates.

   Typically contains :cpp:member:`omdi::GridXY::ny` monotonically increasing
   Y coordinates.

.. cpp:member:: size_t GridXY::nx

   Number of grid points along the X axis.

.. cpp:member:: size_t GridXY::ny

   Number of grid points along the Y axis.

.. cpp:member:: std::vector<float> GridXY::z

   Vector of scalar data on the grid.

   Usually interpreted as a flattened 2D array with size
   ``nx * ny`` (row-major or column-major layout as defined
   by your application).

Constructor
-----------

.. cpp:function:: GridXY::GridXY(const std::vector<float>& x, \
                                 const std::vector<float>& y, \
                                 size_t nx, \
                                 size_t ny, \
                                 const std::vector<float>& z)

   Construct a :cpp:struct:`omdi::GridXY` from coordinate vectors and sizes.

   :param x: Vector of X coordinates (length ``nx``).
   :param y: Vector of Y coordinates (length ``ny``).
   :param nx: Number of grid points along the X axis.
   :param ny: Number of grid points along the Y axis.
   :param z: Vector of scalar grid data (typically of size ``nx * ny``).

   All vectors are copied into the struct; the caller is free to modify
   or destroy the originals after construction.

Notes
-----

- :cpp:struct:`omdi::GridXY` **owns** its coordinate and scalar data; no
  external arrays need to remain alive after construction.
- The layout (row-major vs. column-major) of :cpp:member:`omdi::GridXY::z`
  is application-defined and should be documented wherever the grid is used.
