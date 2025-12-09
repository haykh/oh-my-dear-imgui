#ifndef CORE_STATE_H
#define CORE_STATE_H

#include <toml.hpp>

#include <any>
#include <map>
#include <stdexcept>
#include <string>

namespace omdi {

  /**
   * @brief State manager for storing and retrieving application state variables.
   */
  class State {
    std::map<std::string, std::any> m_state_vars;

  public:
    // Non-template methods
    bool has(const std::string& key) const;
    void remove(const std::string& key);

    // Template methods (must stay in header)
    template <typename T>
    void set(const std::string& key, T&& value) {
      m_state_vars[key] = std::forward<T>(value);
    }

    template <typename T>
    T& get(const std::string& key) {
      auto it = m_state_vars.find(key);
      if (it == m_state_vars.end()) {
        throw std::runtime_error("State::get<T>: key '" + key + "' not found.");
      }

      return std::any_cast<T&>(it->second);
    }

    template <typename T>
    const T& get(const std::string& key) const {
      auto it = m_state_vars.find(key);
      if (it == m_state_vars.end()) {
        throw std::runtime_error("State::get<T>: key '" + key + "' not found.");
      }

      return std::any_cast<const T&>(it->second);
    }

    template <typename T>
    T getOr(const std::string& key, const T& fallback) const {
      auto it = m_state_vars.find(key);
      if (it == m_state_vars.end()) {
        return fallback;
      }

      try {
        return std::any_cast<T>(it->second);
      } catch (const std::bad_any_cast&) {
        return fallback;
      }
    }

    template <typename T>
    void ensure(const std::string& key, const T& default_value) {
      if (not has(key)) {
        set(key, default_value);
      }
    }

    toml::value to_toml() const;
    void        from_toml(const toml::value& v);
  };

} // namespace omdi

#endif // CORE_STATE_H
