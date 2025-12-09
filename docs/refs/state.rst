.. _omdi-state:

State
=====

.. cpp:namespace:: omdi

Overview
--------

.. cpp:class:: State

   State manager for storing and retrieving application state variables.

   The :cpp:class:`omdi::State` class provides a simple key–value store
   for application-level state. Keys are strings and values are stored
   using :cpp:class:`std::any`, allowing arbitrary types to be saved and
   retrieved as long as the same type is used consistently for a given key.

   Internally, state is stored in a :cpp:class:`template\<> std::map\<std::string, std::any>`.

Usage example
-------------

Basic usage with typed access:

.. code-block:: cpp

  omdi::State st;

  // Set values of different types
  st.set<int>("answer", 42);
  st.set<std::string>("mode", "debug");

  // Retrieve them (throws if missing or wrong type)
  int answer = st.get<int>("answer");
  const std::string& mode = st.get<std::string>("mode");

  // Use getOr to provide a fallback if the key is missing or invalid
  bool verbose = st.getOr<bool>("verbose", false);

  // Ensure a default value exists
  st.ensure<std::string>("log_level", "info");

Public interface
----------------

Non-template methods
~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: bool State::has(const std::string& key) const

   Check whether a state variable with the given *key* exists.

   :param key: Name of the state variable.
   :returns: ``true`` if the key exists, ``false`` otherwise.

.. cpp:function:: void State::remove(const std::string& key)

   Remove the state variable associated with *key*, if it exists.

   If the key is not present, the function does nothing.

   :param key: Name of the state variable to remove.

.. cpp:function:: toml::value State::to_toml() const

   Serialize the current state into a :cpp:class:`toml::value`.

   The exact mapping depends on the supported types; typically
   only values that can be represented in TOML are included or
   round-tripped reliably.

   :returns: A TOML value representing the stored state.

.. cpp:function:: void State::from_toml(const toml::value& v)

   Populate the state from a :cpp:class:`toml::value`.

   Existing entries may be overwritten by values from *v*.
   The expected structure of *v* should match what
   :cpp:func:`omdi::State::to_toml` produces.

   :param v: TOML value to load state from.

Template methods
~~~~~~~~~~~~~~~~

.. cpp:function:: template <typename T> void State::set(const std::string& key, T&& value)

   Store a value of type ``T`` under *key*.

   This replaces any existing value stored under the same key.

   :tparam T: Type of the value to store (deduced).
   :param key: Name of the state variable.
   :param value: Value to store. Forwarded into :cpp:class:`std::any`.

   **Exceptions:** May throw any exception thrown by allocation
   or by :cpp:class:`std::any` operations.

.. cpp:function:: template <typename T> T& State::get(const std::string& key)

   Retrieve a non-const reference to the value of type ``T`` stored under *key*.

   :tparam T: Expected type of the stored value.
   :param key: Name of the state variable.
   :returns: Reference to the stored value.

   **Exceptions:**

   - Throws :cpp:class:`std::runtime_error` if *key* is not found.
   - Throws :cpp:class:`std::bad_any_cast` if the stored value cannot be cast to ``T``.

.. cpp:function:: template <typename T> const T& State::get(const std::string& key) const

   Retrieve a const reference to the value of type ``T`` stored under *key*.

   Same semantics as the non-const overload, but returns a const reference.

   :tparam T: Expected type of the stored value.
   :param key: Name of the state variable.
   :returns: Const reference to the stored value.

   **Exceptions:**

   - Throws :cpp:class:`std::runtime_error` if *key* is not found.
   - Throws :cpp:class:`std::bad_any_cast` if the stored value cannot be cast to ``T``.

.. cpp:function:: template <typename T> T State::getOr(const std::string& key, const T& fallback) const

   Retrieve the value of type ``T`` stored under *key*, or return *fallback*
   if the key is missing or the stored value cannot be cast to ``T``.

   :tparam T: Expected type of the stored value and the fallback.
   :param key: Name of the state variable.
   :param fallback: Value to return if the key does not exist or has an incompatible type.
   :returns: The stored value or *fallback*.

   This function does **not** throw for missing keys or type mismatches.

.. cpp:function:: template <typename T> void State::ensure(const std::string& key, const T& default_value)

   Ensure that *key* exists in the state, setting it to *default_value* if it is absent.

   If *key* already exists, the existing value is left unchanged.

   :tparam T: Type of the default value.
   :param key: Name of the state variable.
   :param default_value: Value to store if the key is not present.

Notes
-----

- Internally, all values are stored as :cpp:class:`std::any`. It is the caller’s
  responsibility to use the same type ``T`` when calling :cpp:func:`omdi::State::set`,
  :cpp:func:`omdi::State::get`, and :cpp:func:`omdi::State::getOr` for a given key.
- Use :cpp:func:`omdi::State::getOr` for safe retrieval with a default, and
  :cpp:func:`omdi::State::get` when you want strict behavior and explicit errors.
