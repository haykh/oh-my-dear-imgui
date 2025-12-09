.. _omdi-logger:

Logger
======

.. cpp:namespace:: omdi::logger

Overview
--------

Simple logging utility using ``plog``.

The :cpp:class:`omdi::logger` namespace provides a small wrapper around
the `plog` logging library, with convenience functions for:

- initializing logging with a default severity,
- generic formatted logging with a template severity parameter,
- severity-specific helpers (:cpp:func:`omdi::logger::Debug`,
  :cpp:func:`omdi::logger::Warning`, :cpp:func:`omdi::logger::Error`,
  :cpp:func:`omdi::logger::Fatal`).

Messages are formatted using :cpp:func:`omdi::fmt::vformat` with a
``printf``-style format string and a variable argument list.

Usage example
-------------

Basic initialization and logging:

.. code-block:: cpp

  // Initialize logging with default debug severity
  omdi::logger::Init();

  omdi::logger::Debug("Application started: version=%s", "1.0.0");
  omdi::logger::Warning("Low memory: %d MB remaining", 128);
  omdi::logger::Error("Failed to open file: %s", "data.txt");

  // Generic logging with custom severity (template parameter)
  omdi::logger::Log<plog::info>("User %s logged in", "alice");

  // Fatal logs throw after logging
  try {
    omdi::logger::Fatal("Unrecoverable error: code=%d", -1);
  } catch (const std::runtime_error& e) {
    // Handle or report fatal error
  }
  

Types
-----

.. cpp:type:: Severity = plog::Severity

   Alias for :cpp:type:`plog::Severity`, used to represent log severity levels
   such as ``plog::debug``, ``plog::info``, ``plog::warning``,
   ``plog::error``, and ``plog::fatal``.

Initialization
--------------

.. cpp:function:: void Init(const Severity& minSeverity = plog::debug)

   Initialize the logging system.

   :param minSeverity: Minimum severity level for messages to be logged
                       (defaults to ``plog::debug``).

   This function sets up ``plog`` sinks/appenders according to your
   application’s configuration (implementation-specific). It should typically
   be called once at application startup before any logging occurs.

Generic logging
---------------

.. cpp:function:: template <Severity S = plog::debug> \
                  void Log(const char* fmt, ...)

   Log a formatted message at compile-time-selected severity *S*.

   :tparam S: Compile-time severity level (defaults to ``plog::debug``).
   :param fmt: ``printf``-style format string.
   :param ...: Arguments corresponding to *fmt*.

   Example::

      omdi::logger::Log<plog::info>("Loaded %d items from %s", count, filename);

   Internally, this formats the message with :cpp:func:`omdi::fmt::vformat`
   and sends it to ``plog`` via ``PLOG(S)``.

Severity-specific helpers
-------------------------

.. cpp:function:: void Debug(const char* fmt, ...)

   Log a debug-level message.

   :param fmt: ``printf``-style format string.
   :param ...: Arguments corresponding to *fmt*.

   Equivalent to calling :cpp:func:`omdi::logger::Log` with
   ``S = plog::debug``.

.. cpp:function:: void Warning(const char* fmt, ...)

   Log a warning-level message.

   :param fmt: ``printf``-style format string.
   :param ...: Arguments corresponding to *fmt*.

.. cpp:function:: void Error(const char* fmt, ...)

   Log an error-level message.

   :param fmt: ``printf``-style format string.
   :param ...: Arguments corresponding to *fmt*.

.. cpp:function:: [[noreturn]] void Fatal(const char* fmt, ...)

   Log a fatal-level message and then throw an exception.

   :param fmt: ``printf``-style format string.
   :param ...: Arguments corresponding to *fmt*.

   This function:

   - formats the message using :cpp:func:`omdi::fmt::vformat`,
   - logs it with severity ``plog::fatal``,
   - and then throws :cpp:class:`std::runtime_error` containing the message.

   Because it is marked ``[[noreturn]]``, it is intended for unrecoverable
   errors where normal execution cannot continue.

Notes
-----

- All logging functions use a ``printf``-style interface. The number and types
  of arguments must match the format string.
- The actual configuration of sinks (console, file, etc.) is determined by
  the implementation of :cpp:func:`omdi::logger::Init`.
- :cpp:func:`omdi::logger::Fatal` always throws after logging; callers should
  be prepared to handle :cpp:class:`std::runtime_error` if they wish to catch it.
