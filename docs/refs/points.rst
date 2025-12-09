.. _omdi-points:

Points
======

.. cpp:namespace:: omdi

Overview
--------

.. cpp:struct:: Points

   Structure to hold 2D scattered points data.

   The :cpp:struct:`omdi::Points` struct stores pointers to arrays of
   *x* and *y* coordinates representing **scattered (non-gridded)** 2D points.
   It provides a lightweight, non-owning wrapper around external arrays, and
   is typically used in plotting operations such as scatter plots, line plots,
   or marking features on 2D domains.

   All pointer members are **non-owning**; the caller is responsible for
   ensuring that the underlying arrays remain valid for the lifetime of the
   :cpp:struct:`omdi::Points` instance.

Usage example
-------------

Basic usage with externally allocated arrays:

.. code-block:: cpp

  float xs[] = {0.0f, 1.0f, 2.0f};
  float ys[] = {1.0f, 0.5f, 0.25f};

  auto pts = omdi::Points(xs, ys, 3);

  // pts.x and pts.y now reference the given arrays
  // As long as xs and ys remain alive, pts can be used safely.

Data members
------------

.. cpp:member:: const float* const Points::x

   Pointer to the array of X coordinates.

   Expected to reference an array of length :cpp:member:`omdi::Points::npoints`.

.. cpp:member:: const float* const Points::y

   Pointer to the array of Y coordinates.

   Expected to reference an array of length :cpp:member:`omdi::Points::npoints`.

.. cpp:member:: std::size_t Points::npoints

   Number of scattered points represented by this structure.

Constructor
-----------

.. cpp:function:: Points::Points(const float* x, \
                                 const float* y, \
                                 std::size_t npoints)

   Construct a :cpp:struct:`omdi::Points` object from raw coordinate arrays.

   :param x: Pointer to an array of X coordinates (length ``npoints``).
   :param y: Pointer to an array of Y coordinates (length ``npoints``).
   :param npoints: Number of points in the arrays.

   Both arrays must outlive the :cpp:struct:`omdi::Points` instance.

Notes
-----

- :cpp:struct:`omdi::Points` does **not** own the memory for *x* or *y*.
- All arrays must contain at least :cpp:member:`omdi::Points::npoints` elements.
- The struct is suitable for passing point clouds into plotting primitives,
  proximity queries, or geometric algorithms.
