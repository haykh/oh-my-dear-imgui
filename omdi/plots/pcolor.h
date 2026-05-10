#ifndef PLOTS_PCOLOR_H
#define PLOTS_PCOLOR_H

#include "containers/containers.h"
#include "plots/plot.h"

#include <implot.h>

#include <map>
#include <string>

namespace omdi::plots {

  /**
   * @brief Class for creating 2D heatmap (pseudocolor) plots.
   */
  class PcolorPlot : public Plot,
                     public DataPlot<GridXY> {
    bool           m_aspect_equal { true };
    int            m_which { 0 };
    ImPlotColormap m_colormap { ImPlotColormap_Viridis };

  public:
    PcolorPlot(const std::map<std::string, const GridXY* const>& data,
               const std::string& label        = "PcolorPlot",
               bool               aspect_equal = true)
      : Plot { label }
      , DataPlot { data }
      , m_aspect_equal { aspect_equal } {}

    void plot() override;
  };

} // namespace omdi::plots

#endif // PLOTS_PCOLOR_H
