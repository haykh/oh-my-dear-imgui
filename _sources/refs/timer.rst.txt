.. _omdi-timer:

Timer
=====

Overview
--------

.. cpp:class:: omdi::Timer

   Timer class for measuring elapsed time and frame delta time.

   The :cpp:class:`omdi::Timer` class provides a simple high-resolution
   timer suitable for render loops and simulations. It measures:

   - the total elapsed time since construction, and
   - the per-frame delta time between consecutive :cpp:func:`omdi::Timer::tick` calls.

   Internally, it uses :cpp:type:`std::chrono::high_resolution_clock`.

Data members
------------

.. cpp:member:: std::chrono::time_point<std::chrono::high_resolution_clock> omdi::Timer::m_now

   Timestamp of the most recent frame (last call to :cpp:func:`omdi::Timer::tick`).

.. cpp:member:: const std::chrono::time_point<std::chrono::high_resolution_clock> omdi::Timer::m_start

   Timestamp when the timer was constructed.

   This value is constant for the lifetime of the timer and is used as the
   reference for computing total elapsed time.

.. cpp:member:: std::size_t omdi::Timer::m_frame

   Current frame counter.

   Incremented by :cpp:func:`omdi::Timer::tick` each time it is called.

.. cpp:member:: double omdi::Timer::m_delta

   Time in seconds between the last two frames.

   Updated on each call to :cpp:func:`omdi::Timer::tick`. Initialized to ``1.0``.

.. cpp:member:: double omdi::Timer::m_elapsed

   Total elapsed time in seconds since the timer was constructed.

   Updated on each call to :cpp:func:`omdi::Timer::tick`.

Constructor
-----------

.. cpp:function:: omdi::Timer::Timer()

   Construct a timer and initialize timestamps.

   Sets :cpp:member:`omdi::Timer::m_now` and
   :cpp:member:`omdi::Timer::m_start` to the current
   :cpp:type:`std::chrono::high_resolution_clock` time, with frame
   counter, delta, and elapsed values initialized accordingly.

Public interface
----------------

.. cpp:function:: void omdi::Timer::tick()

   Advance the timer by one frame.

   This function:

   - obtains the current time from
     :cpp:type:`std::chrono::high_resolution_clock`,
   - updates :cpp:member:`omdi::Timer::m_elapsed` with the total elapsed
     seconds since :cpp:member:`omdi::Timer::m_start`,
   - updates :cpp:member:`omdi::Timer::m_delta` with the time difference
     (in seconds) between the new timestamp and the previous
     :cpp:member:`omdi::Timer::m_now`,
   - stores the new timestamp in :cpp:member:`omdi::Timer::m_now`,
   - increments :cpp:member:`omdi::Timer::m_frame`.

   Typically called once per frame in the main loop.

.. cpp:function:: std::size_t omdi::Timer::frame() const

   Get the current frame count.

   :returns: Number of times :cpp:func:`omdi::Timer::tick` has been called
             since construction.

.. cpp:function:: double omdi::Timer::delta() const

   Get the time elapsed between the last two frames.

   :returns: Delta time in seconds (as updated by the most recent
             :cpp:func:`omdi::Timer::tick` call).

.. cpp:function:: double omdi::Timer::elapsed() const

   Get the total elapsed time since the timer was constructed.

   :returns: Elapsed time in seconds since
             :cpp:member:`omdi::Timer::m_start`.
