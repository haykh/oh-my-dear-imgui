#include "examples/field.h"

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace omdi::examples {

  OscillatingFields::OscillatingFields(
    const std::vector<std::pair<std::string, std::function<float(float, float, double)>>>& settings,
    const std::tuple<float, float, std::size_t>& x_axis,
    const std::tuple<float, float, std::size_t>& y_axis)
    : m_nx { std::get<2>(x_axis) }
    , m_ny { std::get<2>(y_axis) } {
    m_x      = new float[m_nx];
    m_y      = new float[m_ny];
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
      m_fields.push_back(new float[m_nx * m_ny]);
      m_functions.push_back(func);
      for (auto j = 0u; j < m_ny; ++j) {
        for (auto i = 0u; i < m_nx; ++i) {
          m_fields.back()[IDX(i, j)] = func(m_x[i], m_y[j], 0.0);
        }
      }
    }
  }

  OscillatingFields::~OscillatingFields() {
    delete[] m_x;
    delete[] m_y;
    for (auto ptr : m_fields) {
      delete[] ptr;
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

  auto OscillatingFields::get_data() const
    -> std::map<std::string, const omdi::GridXY* const> {
    auto field_groups = std::map<std::string, const omdi::GridXY* const> {};
    for (auto group = 0u; group < n_groups(); ++group) {
      field_groups.insert({
        m_labels[group],
        new omdi::GridXY { m_x, m_y, m_nx, m_ny, m_fields[group] }
      });
    }
    return field_groups;
  }

} // namespace omdi::examples
