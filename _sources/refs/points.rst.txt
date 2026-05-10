.. _omdi-points:

Points
======

.. cpp:namespace:: omdi

Overview
--------

.. cpp:struct:: Points

   Structure to hold 2D scattered points data.

   The :cpp:struct:`omdi::Points` struct stores and **owns** vectors of
   *x* and *y* coordinates representing **scattered (non-gridded)** 2D points.
   Data is copied into the struct on construction, so the caller does not need
   to keep the source arrays alive after creating a :cpp:struct:`omdi::Points`
   instance.

   It is typically used in plotting operations such as scatter plots, line plots,
   or marking features on 2D domains.

Usage example
-------------

Basic usage with ``std::vector`` arrays:

.. code-block:: cpp

  auto xs = std::vector<float> { 0.0f, 1.0f, 2.0f };
  auto ys = std::vector<float> { 1.0f, 0.5f, 0.25f };

  auto pts = omdi::Points(xs, ys, 3);

  // pts.x and pts.y are independent copies of xs and ys.
  // The source vectors may safely go out of scope.

Data members
------------

.. cpp:member:: std::vector<float> Points::x

   Vector of X coordinates.

   Contains :cpp:member:`omdi::Points::npoints` elements.

.. cpp:member:: std::vector<float> Points::y

   Vector of Y coordinates.

   Contains :cpp:member:`omdi::Points::npoints` elements.

.. cpp:member:: size_t Points::npoints

   Number of scattered points represented by this structure.

Constructor
-----------

.. cpp:function:: Points::Points(const std::vector<float>& x, \
                                 const std::vector<float>& y, \
                                 size_t npoints)

   Construct a :cpp:struct:`omdi::Points` object from coordinate vectors.

   :param x: Vector of X coordinates (length ``npoints``).
   :param y: Vector of Y coordinates (length ``npoints``).
   :param npoints: Number of points in the arrays.

   Both vectors are copied into the struct; the caller is free to modify
   or destroy the originals after construction.

Notes
-----

- :cpp:struct:`omdi::Points` **owns** its coordinate data; no external arrays
  need to remain alive after construction.
- Both vectors must contain at least :cpp:member:`omdi::Points::npoints` elements.
- The struct is suitable for passing point clouds into plotting primitives,
  proximity queries, or geometric algorithms.
