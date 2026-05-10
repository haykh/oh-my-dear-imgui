#ifndef EXAMPLES_POINTCLOUD_H
#define EXAMPLES_POINTCLOUD_H

#include "containers/containers.h"
#include "examples/sim.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace omdi::examples {

  class RotatingPointcloud : public Sim {
    std::vector<std::vector<float>> m_xPos;
    std::vector<std::vector<float>> m_yPos;
    std::vector<size_t>             m_npoints;
    std::vector<std::string>        m_labels;

  public:
    RotatingPointcloud(const std::vector<std::pair<std::string, size_t>>&);

    void update(double, double) override;

    auto n_groups() const -> size_t {
      return m_labels.size();
    }

    auto get_data() const -> std::map<std::string, omdi::Points>;
  };

} // namespace omdi::examples

#endif // EXAMPLES_POINTCLOUD_H
