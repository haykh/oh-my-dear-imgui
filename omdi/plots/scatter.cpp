#include "plots/scatter.h"

#include <implot.h>

namespace omdi::plots {

  void ScatterPlot::plot() {
    if (ImPlot::BeginPlot(label().c_str(),
                          ImVec2(-1, -1),
                          m_aspect_equal ? ImPlotFlags_Equal : ImPlotFlags_None)) {
      for (const auto& [lbl, points] : m_data) {
        ImPlot::PlotScatter(lbl.c_str(), points->x, points->y, points->npoints);
      }
      ImPlot::EndPlot();
    }
  }

} // namespace omdi::plots
