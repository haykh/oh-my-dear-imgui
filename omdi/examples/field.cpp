#include "examples/field.h"

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace omdi::examples {

  OscillatingFields::OscillatingFields(
    const std::vector<std::pair<std::string, std::function<float(float, float, double)>>>& settings,
    const std::tuple<float, float, size_t>& x_axis,
    const std::tuple<float, float, size_t>& y_axis)
    : m_nx { std::get<2>(x_axis) }
    , m_ny { std::get<2>(y_axis) }
    , m_x(m_nx)
    , m_y(m_ny) {
    float dx = (std::get<1>(x_axis) - std::get<0>(x_axis)) / (m_nx - 1);
    for (auto i = 0u; i < m_nx; ++i) {
      m_x[i] = std::get<0>(x_axis) + i * dx;
    }
    float dy = (std::get<1>(y_axis) - std::get<0>(y_axis)) / (m_ny - 1);
    for (auto j = 0u; j < m_ny; ++j) {
      m_y[j] = std::get<0>(y_axis) + j * dy;
    }
    const auto IDX = [&](auto i, auto j) {
      return j * m_nx + i;
    };
    for (const auto& [label, func] : settings) {
      m_labels.push_back(label);
      m_fields.emplace_back(m_nx * m_ny);
      m_functions.push_back(func);
      for (auto j = 0u; j < m_ny; ++j) {
        for (auto i = 0u; i < m_nx; ++i) {
          m_fields.back()[IDX(i, j)] = func(m_x[i], m_y[j], 0.0);
        }
      }
    }
  }

  void OscillatingFields::update(double time, double) {
    const auto IDX = [&](auto i, auto j) {
      return j * m_nx + i;
    };
    for (auto group = 0u; group < n_groups(); ++group) {
      for (auto j = 0u; j < m_ny; ++j) {
        for (auto i = 0u; i < m_nx; ++i) {
          m_fields[group][IDX(i, j)] = m_functions[group](m_x[i], m_y[j], time);
        }
      }
    }
  }

  auto OscillatingFields::get_data() const -> std::map<std::string, omdi::GridXY> {
    std::map<std::string, omdi::GridXY> result;
    for (auto group = 0u; group < n_groups(); ++group) {
      result.emplace(std::piecewise_construct,
                     std::forward_as_tuple(m_labels[group]),
                     std::forward_as_tuple(m_x, m_y, m_nx, m_ny, m_fields[group]));
    }
    return result; // NRVO
  }

} // namespace omdi::examples
