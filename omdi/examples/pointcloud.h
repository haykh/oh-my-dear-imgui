#ifndef EXAMPLES_POINTCLOUD_H
#define EXAMPLES_POINTCLOUD_H

#include "examples/sim.h"
#include "plots/containers.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace omdi::examples {

  class RotatingPointcloud : public Sim {
    std::vector<float*>      m_xPos;
    std::vector<float*>      m_yPos;
    std::vector<std::size_t> m_npoints;
    std::vector<std::string> m_labels;

  public:
    RotatingPointcloud(const std::vector<std::pair<std::string, std::size_t>>&);

    ~RotatingPointcloud();

    void update(double, double) override;

    auto n_groups() const -> std::size_t {
      return m_labels.size();
    }

    auto get_data() const
      -> std::map<std::string, const omdi::plots::Points* const>;
  };

} // namespace omdi::examples

#endif // EXAMPLES_POINTCLOUD_H
