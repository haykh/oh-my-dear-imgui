#include "plots/pcolor.h"

#include "plots/renderers/heatmap_cart.h"

#include <implot.h>

namespace omdi::plots {

  void BustItemCache() {
    ImPlotContext& gp = *GImPlot;
    for (int p = 0; p < gp.Plots.GetBufSize(); ++p) {
      ImPlotPlot& plot = *gp.Plots.GetByIndex(p);
      plot.Items.Reset();
    }
    for (int p = 0; p < gp.Subplots.GetBufSize(); ++p) {
      ImPlotSubplot& subplot = *gp.Subplots.GetByIndex(p);
      subplot.Items.Reset();
    }
  }

  void BustColorCache(const char* plot_title_id) {
    ImPlotContext& gp = *GImPlot;
    if (plot_title_id == nullptr) {
      BustItemCache();
    } else {
      ImGuiID     id   = ImGui::GetCurrentWindow()->GetID(plot_title_id);
      ImPlotPlot* plot = gp.Plots.GetByKey(id);
      if (plot != nullptr) {
        plot->Items.Reset();
      } else {
        ImPlotSubplot* subplot = gp.Subplots.GetByKey(id);
        if (subplot != nullptr) {
          subplot->Items.Reset();
        }
      }
    }
  }

  void PcolorPlot::plot() {
    auto counter = 0;
    for (const auto& [name, grid] : data) {
      if (counter == which) {
        static ImPlotColormap map = ImPlotColormap_Viridis;
        if (ImPlot::ColormapButton(ImPlot::GetColormapName(map), ImVec2(225, 0), map)) {
          map = (map + 1) % ImPlot::GetColormapCount();
          // We bust the color cache of our plots so that item colors will
          // resample the new colormap in the event that they have already
          // been created. See documentation in implot.h.
          BustColorCache("##Heatmap1");
          BustColorCache("##Heatmap2");
        }
        if (ImPlot::BeginPlot(label.c_str(),
                              ImVec2(-1, -1),
                              aspect_equal ? ImPlotFlags_Equal : ImPlotFlags_None)) {
          ImPlot::PushColormap(map);
          renderers::PlotHeatmapCart(
            name.c_str(),
            grid->z,
            grid->nx,
            grid->ny,
            -1.0,
            1.0,
            false,
            ImPlotPoint(grid->x[0], grid->y[0]),
            ImPlotPoint(grid->x[grid->nx - 1], grid->y[grid->ny - 1]),
            ImPlotAxisFlags_NoGridLines);
          ImPlot::PopColormap();
          ImPlot::EndPlot();
        }
        break;
      }
      ++counter;
    }
  }

} // namespace omdi::plots
