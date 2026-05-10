.. _omdi-example-oscillating-fields:

OscillatingFields
=================

.. cpp:namespace:: omdi::examples

Overview
--------

.. cpp:class:: OscillatingFields : public omdi::examples::Sim

   Built-in example simulation that animates one or more 2D scalar fields
   using user-supplied mathematical functions.

   :cpp:class:`omdi::examples::OscillatingFields` generates a regular 2D
   grid for each named field, evaluating a user-provided callable
   ``f(x, y, time)`` at every grid point on each :cpp:func:`update` call.
   The resulting :cpp:struct:`omdi::GridXY` objects are returned by
   :cpp:func:`get_data` and can be passed directly to
   :cpp:class:`omdi::PcolorPlot`.

   It is a convenient starting point for visualizing oscillating or
   time-varying 2D phenomena such as wave interference patterns, standing
   waves, or physical fields.

Usage example
-------------

.. code-block:: cpp

  #include <omdi.hpp>

  // Define field functions (signature: float(float x, float y, double time))
  auto wave = [](float x, float y, double t) -> float {
    return std::sinf(x * 6.28f + (float)t) * std::cosf(y * 6.28f + 1.5f * (float)t);
  };

  // Construct with a list of (name, function) pairs and grid ranges
  auto sim = omdi::examples::OscillatingFields(
    { { "wave", wave } },
    { -2.0f, 2.0f, 256 },   // x: (min, max, nx)
    { -2.0f, 2.0f, 256 }    // y: (min, max, ny)
  );

  // Create a PcolorPlot to display the fields
  auto pcolor = omdi::PcolorPlot { "Fields", sim.get_data() };

  // Inside the render loop:
  auto timer = omdi::Timer();

  app.Render(&state, [&]() {
    sim.update(timer.elapsed(), timer.delta());
    pcolor.update_all(sim.get_data());
    pcolor.plot();
    timer.tick();
  }, components, managers);

Constructor
-----------

.. cpp:function:: OscillatingFields::OscillatingFields( \
     const std::vector<std::pair<std::string, std::function<float(float, float, double)>>>& fields, \
     const std::tuple<float, float, size_t>& x_range, \
     const std::tuple<float, float, size_t>& y_range)

   Construct an ``OscillatingFields`` simulation.

   :param fields: List of ``(name, function)`` pairs. Each function must
                  have the signature ``float(float x, float y, double time)``
                  and will be evaluated at every grid point on each
                  :cpp:func:`update` call.
   :param x_range: Tuple ``(min, max, nx)`` describing the X axis: minimum
                   value, maximum value, and number of grid points.
   :param y_range: Tuple ``(min, max, ny)`` describing the Y axis: minimum
                   value, maximum value, and number of grid points.

Public interface
----------------

.. cpp:function:: void OscillatingFields::update(double time, double delta)

   Advance the simulation by one step.

   Re-evaluates each field function at all grid points using the given
   ``time`` value. The results are stored internally and can be retrieved
   with :cpp:func:`get_data`.

   :param time: Absolute simulation time (seconds).
   :param delta: Time elapsed since the last update (seconds). Currently
                 unused by the built-in implementation but forwarded for
                 compatibility with :cpp:struct:`omdi::examples::Sim`.

.. cpp:function:: auto OscillatingFields::n_groups() const -> size_t

   Return the number of named field groups managed by this simulation.

   :returns: Number of ``(name, function)`` pairs passed to the constructor.

.. cpp:function:: auto OscillatingFields::get_data() const -> std::map<std::string, omdi::GridXY>

   Return the current field data for all groups.

   :returns: A map from field name to the corresponding
             :cpp:struct:`omdi::GridXY`, containing the most recently
             computed scalar values. The map is returned by value; the
             caller owns the result.

Notes
-----

- The returned map from :cpp:func:`get_data` can be passed directly to
  :cpp:func:`omdi::PcolorPlot::update_all` to refresh all series at once.
- The grid coordinates (x, y axes) are computed once in the constructor
  and do not change between updates; only the z values are recomputed.
- :cpp:class:`omdi::examples::OscillatingFields` is declared in
  ``examples/field.h`` and is included automatically via ``omdi.hpp``.
