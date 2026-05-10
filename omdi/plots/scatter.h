#ifndef PLOTS_SCATTER_H
#define PLOTS_SCATTER_H

#include "containers/containers.h"
#include "plots/plot.h"

#include <implot.h>

#include <map>
#include <string>

namespace omdi::plots {

  /**
   * @brief Class for creating 2D scatter plots.
   */
  class ScatterPlot : public Plot,
                      public DataPlot<Points> {
    bool m_aspect_equal = true;

  public:
    ScatterPlot(const std::string&                   label = "ScatterPlot",
                const std::map<std::string, Points>& data  = {},
                bool                                 aspect_equal = true)
      : Plot { label }
      , DataPlot { data }
      , m_aspect_equal { aspect_equal } {}

    void plot() override;
  };

}; // namespace omdi::plots

#endif // PLOTS_SCATTER_H
