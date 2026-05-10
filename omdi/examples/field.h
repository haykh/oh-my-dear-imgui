#ifndef EXAMPLES_FIELD_H
#define EXAMPLES_FIELD_H

#include "containers/containers.h"
#include "examples/sim.h"

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace omdi::examples {

  class OscillatingFields : public Sim {
    std::vector<std::function<float(float, float, double)>> m_functions;
    std::vector<std::vector<float>>                         m_fields;
    std::vector<std::string>                                m_labels;
    size_t                                                  m_nx;
    size_t                                                  m_ny;
    std::vector<float>                                      m_x;
    std::vector<float>                                      m_y;

  public:
    // takes in string -> function (x, y) -> float
    OscillatingFields(
      const std::vector<std::pair<std::string, std::function<float(float, float, double)>>>&,
      const std::tuple<float, float, size_t>&,
      const std::tuple<float, float, size_t>&);

    void update(double, double) override;

    auto n_groups() const -> size_t {
      return m_labels.size();
    }

    auto get_data() const -> std::map<std::string, omdi::GridXY>;
  };

} // namespace omdi::examples

#endif // EXAMPLES_FIELD_H
