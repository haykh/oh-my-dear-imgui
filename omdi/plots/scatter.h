#ifndef PLOTS_SCATTER_H
#define PLOTS_SCATTER_H

#include "containers/containers.h"
#include "plots/plot.h"

#include <map>
#include <string>

namespace omdi::plots {

  /**
   * @brief Class for creating 2D scatter plots.
   */
  class ScatterPlot : public Plot {
    bool m_aspect_equal = true;

    std::map<std::string, const Points* const> m_data;

  public:
    ScatterPlot(const std::map<std::string, const Points* const>& data,
                const std::string& label        = "ScatterPlot",
                bool               aspect_equal = true)
      : Plot { label }
      , m_data { data }
      , m_aspect_equal { aspect_equal } {}

    void plot() override;
  };

}; // namespace omdi::plots

#endif // PLOTS_SCATTER_H
