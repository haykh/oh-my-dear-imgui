#include "managers/state.h"

#include <imgui.h>
#include <toml.hpp>

#include <string>

namespace omdi::state {

  bool State::has(const std::string& key) const {
    return m_state_vars.find(key) != m_state_vars.end();
  }

  void State::remove(const std::string& key) {
    m_state_vars.erase(key);
  }

  auto State::to_toml() const -> toml::value {
    toml::value table { toml::value::table_type {} };

    for (const auto& [key, value] : m_state_vars) {
      if (value.type() == typeid(int)) {
        table[key] = std::any_cast<int>(value);
      } else if (value.type() == typeid(double)) {
        table[key] = std::any_cast<double>(value);
      } else if (value.type() == typeid(bool)) {
        table[key] = std::any_cast<bool>(value);
      } else if (value.type() == typeid(std::string)) {
        table[key] = std::any_cast<std::string>(value);
      } else if (value.type() == typeid(std::vector<int>)) {
        table[key] = std::any_cast<std::vector<int>>(value);
      } else if (value.type() == typeid(std::vector<std::string>)) {
        table[key] = std::any_cast<std::vector<std::string>>(value);
      } else if (value.type() == typeid(ImVec2)) {
        auto v                 = std::any_cast<ImVec2>(value);
        table[key + "_IMVEC2"] = toml::array { v.x, v.y };
      } else if (value.type() == typeid(ImVec4)) {
        auto v                 = std::any_cast<ImVec4>(value);
        table[key + "_IMVEC4"] = toml::array { v.x, v.y, v.z, v.w };
      } else {
        // Unsupported type
        throw std::runtime_error("Unsupported type for key: " + key);
      }
    }

    return table;
  }

  void State::from_toml(const toml::value& v) {
    if (!v.is_table()) {
      throw std::runtime_error("Invalid TOML format: expected a table");
    }

    // Helper to check suffix
    auto ends_with = [](const std::string& str, const std::string& suffix) -> bool {
      return str.size() >= suffix.size() &&
             str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    };

    // Helper to strip suffix
    auto strip_suffix = [&](const std::string& key,
                            const std::string& suffix) -> std::optional<std::string> {
      if (ends_with(key, suffix)) {
        return key.substr(0, key.size() - suffix.size());
      }
      return std::nullopt;
    };

    // Helper to convert array to vector<T>
    auto as_vector = [](const toml::array& arr, auto converter) {
      using T = decltype(converter(arr[0]));
      std::vector<T> out;
      out.reserve(arr.size());
      for (const auto& val : arr) {
        out.push_back(converter(val));
      }
      return out;
    };

    for (const auto& [key, val] : v.as_table()) {
      if (auto base = strip_suffix(key, "_IMVEC2")) {
        if (val.is_array() && val.as_array().size() == 2) {
          const auto& arr     = val.as_array();
          m_state_vars[*base] = ImVec2 { (float)arr[0].as_floating(),
                                         (float)arr[1].as_floating() };
          continue;
        }
      }

      if (auto base = strip_suffix(key, "_IMVEC4")) {
        if (val.is_array() && val.as_array().size() == 4) {
          const auto& arr     = val.as_array();
          m_state_vars[*base] = ImVec4 { (float)arr[0].as_floating(),
                                         (float)arr[1].as_floating(),
                                         (float)arr[2].as_floating(),
                                         (float)arr[3].as_floating() };
          continue;
        }
      }

      // Standard types
      if (val.is_integer()) {
        m_state_vars[key] = val.as_integer();
      } else if (val.is_floating()) {
        m_state_vars[key] = val.as_floating();
      } else if (val.is_boolean()) {
        m_state_vars[key] = val.as_boolean();
      } else if (val.is_string()) {
        m_state_vars[key] = val.as_string();
      } else if (val.is_array()) {
        const auto& arr = val.as_array();
        if (arr.empty()) {
          continue;
        }

        if (arr[0].is_integer()) {
          m_state_vars[key] = as_vector(arr, [](const toml::value& v) {
            return v.as_integer();
          });
        } else if (arr[0].is_floating()) {
          m_state_vars[key] = as_vector(arr, [](const toml::value& v) {
            return v.as_floating();
          });
        } else if (arr[0].is_string()) {
          m_state_vars[key] = as_vector(arr, [](const toml::value& v) {
            return v.as_string();
          });
        }
      }
    }
  }

} // namespace omdi::state
