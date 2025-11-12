#ifndef EXAMPLES_FIELD_H
#define EXAMPLES_FIELD_H

#include "plots/containers.h"

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace omdi::examples {

  class OscillatingFields {
    std::vector<std::function<float(float, float, double)>> m_functions;
    std::vector<float*>                                     m_fields;
    std::vector<std::string>                                m_labels;
    float*                                                  m_x;
    float*                                                  m_y;
    std::size_t                                             m_nx;
    std::size_t                                             m_ny;

  public:
    // takes in string -> function (x, y) -> float
    OscillatingFields(
      const std::vector<std::pair<std::string, std::function<float(float, float, double)>>>&,
      const std::tuple<float, float, std::size_t>&,
      const std::tuple<float, float, std::size_t>&);

    ~OscillatingFields();

    void update(double, double);

    auto n_groups() const -> std::size_t {
      return m_labels.size();
    }

    auto get_data() const
      -> std::map<std::string, const omdi::plots::GridXY* const>;
  };

} // namespace omdi::examples

#endif // EXAMPLES_FIELD_H
