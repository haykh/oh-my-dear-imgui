.. _omdi-grid-xy:

GridXY
======

.. cpp:namespace:: omdi

Overview
--------

.. cpp:struct:: GridXY

   Structure to hold 2D grid data.

   The :cpp:struct:`omdi::GridXY` struct stores pointers to the X and Y
   coordinate axes of a regular 2D grid, along with the grid dimensions
   and a pointer to the associated scalar data ``z``.

   All pointer members are **non-owning**; the caller is responsible for
   ensuring that the pointed-to data remains valid for the lifetime of
   the :cpp:struct:`omdi::GridXY` instance.

Usage example
-------------

Basic usage with externally owned data:

.. code-block:: cpp

  constexpr std::size_t nx = 3;
  constexpr std::size_t ny = 2;

  float xs[nx] = {0.0f, 1.0f, 2.0f};
  float ys[ny] = {0.0f, 1.0f};
  float zs[nx * ny] = {
      0.0f, 1.0f,
      2.0f, 3.0f,
      4.0f, 5.0f
  };

  auto grid = omdi::GridXY(xs, ys, nx, ny, zs);

Data members
------------

.. cpp:member:: const float* const GridXY::x

   Pointer to the X coordinates array.

   Typically points to an array of length :cpp:member:`omdi::GridXY::nx`,
   containing monotonically increasing X coordinates.

.. cpp:member:: const float* const GridXY::y

   Pointer to the Y coordinates array.

   Typically points to an array of length :cpp:member:`omdi::GridXY::ny`,
   containing monotonically increasing Y coordinates.

.. cpp:member:: std::size_t GridXY::nx

   Number of grid points along the X axis.

.. cpp:member:: std::size_t GridXY::ny

   Number of grid points along the Y axis.

.. cpp:member:: const float* const GridXY::z

   Pointer to the scalar data on the grid.

   Usually interpreted as a flattened 2D array with size
   ``nx * ny`` (row-major or column-major layout as defined
   by your application).

Constructor
-----------

.. cpp:function:: GridXY::GridXY(const float* x, \
                                 const float* y, \
                                 std::size_t nx, \
                                 std::size_t ny, \
                                 const float* z)

   Construct a :cpp:struct:`omdi::GridXY` from raw pointers and sizes.

   :param x: Pointer to the X coordinate array (length ``nx``).
   :param y: Pointer to the Y coordinate array (length ``ny``).
   :param nx: Number of grid points along the X axis.
   :param ny: Number of grid points along the Y axis.
   :param z: Pointer to the scalar grid data (typically of size ``nx * ny``).

Notes
-----

- :cpp:struct:`omdi::GridXY` does **not** allocate or own memory; it simply
  stores pointers and sizes.
- The layout (row-major vs. column-major) of :cpp:member:`omdi::GridXY::z`
  is application-defined and should be documented wherever the grid is used.
