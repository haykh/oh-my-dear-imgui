#include "implot-gpu/implot.h"
#include "implot-gpu/plotters.h"

#include "plots/pcolor.h"

#include <implot.h>

namespace omdi::plots {

  void PcolorPlot::plot() {
    auto counter = 0;
    for (const auto& [name, grid] : m_data) {
      if (counter == m_which) {
        if (ImPlot::ColormapButton(ImPlot::GetColormapName(m_colormap),
                                   ImVec2(225, 0),
                                   m_colormap)) {
          m_colormap = (m_colormap + 1) % ImPlot::GetColormapCount();
          omdi::implot::BustColorCache(label().c_str());
        }
        ImPlot::PushColormap(m_colormap);
        if (ImPlot::BeginPlot(label().c_str(),
                              ImVec2(-1, -1),
                              m_aspect_equal ? ImPlotFlags_Equal
                                             : ImPlotFlags_None)) {
          omdi::implot::PlotHeatmap(
            name.c_str(),
            grid->z,
            grid->ny,
            grid->nx,
            -1.0,
            1.0,
            ImPlotPoint(grid->x[0], grid->y[0]),
            ImPlotPoint(grid->x[grid->nx - 1], grid->y[grid->ny - 1]),
            ImPlotAxisFlags_NoGridLines);
          ImPlot::EndPlot();
        }
        ImPlot::PopColormap();
        break;
      }
      ++counter;
    }
  }

} // namespace omdi::plots
