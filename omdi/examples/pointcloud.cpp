#include "examples/pointcloud.h"

#include "plots/containers.h"

#include <cmath>

#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace omdi::examples {

  RotatingPointcloud::RotatingPointcloud(
    const std::vector<std::pair<std::string, std::size_t>>& settings) {
    for (const auto& [label, npoints] : settings) {
      m_labels.push_back(label);
      m_npoints.push_back(npoints);
      m_xPos.push_back(new float[npoints]);
      m_yPos.push_back(new float[npoints]);
    }

    std::random_device               rd;
    std::mt19937                     gen(rd());
    std::uniform_real_distribution<> rnd;
    for (auto group = 0u; group < n_groups(); ++group) {
      const auto npoints = m_npoints[group];
      for (auto i = 0u; i < npoints; ++i) {
        const auto u1    = rnd(gen);
        const auto u2    = rnd(gen);
        m_xPos[group][i] = std::sqrt(-2.0f * std::log(u1)) *
                           std::cos(2.0f * M_PI * u2);
        m_yPos[group][i] = std::sqrt(-2.0f * std::log(u1)) *
                           std::sin(2.0f * M_PI * u2);
      }
    }
  }

  RotatingPointcloud::~RotatingPointcloud() {
    for (auto group = 0u; group < n_groups(); ++group) {
      delete[] m_xPos[group];
      delete[] m_yPos[group];
    }
  }

  void RotatingPointcloud::update(double, double delta) {
    for (auto group = 0u; group < n_groups(); ++group) {
      const auto npoints = m_npoints[group];
      for (auto i = 0u; i < npoints; ++i) {
        const auto r     = std::sqrt(m_xPos[group][i] * m_xPos[group][i] +
                                 m_yPos[group][i] * m_yPos[group][i]);
        const auto omega = 1.0 / (0.25 + r);
        const auto angle = std::atan2(m_yPos[group][i], m_xPos[group][i]) +
                           omega * 0.1f * delta;
        m_xPos[group][i] = r * std::cos(angle);
        m_yPos[group][i] = r * std::sin(angle);
      }
    }
  }

  auto RotatingPointcloud::get_data() const
    -> std::map<std::string, const omdi::plots::Points* const> {
    auto point_groups = std::map<std::string, const omdi::plots::Points* const> {};
    for (auto group = 0u; group < n_groups(); ++group) {
      point_groups.insert({
        m_labels[group],
        new omdi::plots::Points { m_xPos[group], m_yPos[group], m_npoints[group] }
      });
    }
    return point_groups;
  }

} // namespace omdi::examples
