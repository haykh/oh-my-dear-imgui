.. _omdi-example-rotating-pointcloud:

RotatingPointcloud
==================

.. cpp:namespace:: omdi::examples

Overview
--------

.. cpp:class:: RotatingPointcloud : public omdi::examples::Sim

   Built-in example simulation that animates one or more rotating 2D point
   clouds.

   :cpp:class:`omdi::examples::RotatingPointcloud` manages a set of named
   point groups, each containing a fixed number of randomly distributed 2D
   points. On each :cpp:func:`update` call the groups are rotated by an
   angle proportional to the elapsed time, producing a smooth spinning
   animation. The resulting :cpp:struct:`omdi::Points` objects are returned
   by :cpp:func:`get_data` and can be passed directly to
   :cpp:class:`omdi::ScatterPlot`.

   It is a convenient starting point for testing and demonstrating
   :cpp:class:`omdi::ScatterPlot` with live, time-varying data.

Usage example
-------------

.. code-block:: cpp

  #include <omdi.hpp>

  // Construct with a list of (name, npoints) pairs
  auto sim = omdi::examples::RotatingPointcloud({
    { "group A", 500 },
    { "group B", 300 }
  });

  // Create a ScatterPlot to display the point clouds
  auto scatter = omdi::ScatterPlot { "Pointcloud", sim.get_data() };

  // Inside the render loop:
  auto timer = omdi::Timer();

  app.Render(&state, [&]() {
    sim.update(timer.elapsed(), timer.delta());
    scatter.update_all(sim.get_data());
    scatter.plot();
    timer.tick();
  }, components, managers);

Constructor
-----------

.. cpp:function:: RotatingPointcloud::RotatingPointcloud( \
     const std::vector<std::pair<std::string, size_t>>& groups)

   Construct a ``RotatingPointcloud`` simulation.

   :param groups: List of ``(name, npoints)`` pairs. For each pair a group
                  of ``npoints`` randomly positioned 2D points is created
                  and associated with the given name.

Public interface
----------------

.. cpp:function:: void RotatingPointcloud::update(double time, double delta)

   Advance the simulation by one step.

   Rotates every point group by an angle derived from the current ``time``,
   producing continuous rotation. The updated positions are stored internally
   and can be retrieved with :cpp:func:`get_data`.

   :param time: Absolute simulation time (seconds).
   :param delta: Time elapsed since the last update (seconds). Currently
                 unused by the built-in implementation but forwarded for
                 compatibility with :cpp:struct:`omdi::examples::Sim`.

.. cpp:function:: auto RotatingPointcloud::n_groups() const -> size_t

   Return the number of named point groups managed by this simulation.

   :returns: Number of ``(name, npoints)`` pairs passed to the constructor.

.. cpp:function:: auto RotatingPointcloud::get_data() const -> std::map<std::string, omdi::Points>

   Return the current point data for all groups.

   :returns: A map from group name to the corresponding
             :cpp:struct:`omdi::Points`, containing the most recently
             computed point positions. The map is returned by value; the
             caller owns the result.

Notes
-----

- The returned map from :cpp:func:`get_data` can be passed directly to
  :cpp:func:`omdi::ScatterPlot::update_all` to refresh all series at once.
- Initial point positions are randomized in the constructor and then
  rotated rigidly on each :cpp:func:`update` call; the number of points per
  group does not change over time.
- :cpp:class:`omdi::examples::RotatingPointcloud` is declared in
  ``examples/pointcloud.h`` and is included automatically via ``omdi.hpp``.
