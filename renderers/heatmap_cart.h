#ifndef PLOTS_RENDERERS_HEATMAP_CART_H
#define PLOTS_RENDERERS_HEATMAP_CART_H

#include <implot.h>
#include <implot_internal.h>

namespace omdi::plots::renderers {

  template <typename T>
  void PlotHeatmapCart(const char*,
                       const T*,
                       int,
                       int,
                       double,
                       double,
                       bool,
                       const ImPlotPoint&,
                       const ImPlotPoint&,
                       ImPlotHeatmapFlags);

} // namespace omdi::plots::renderers

#endif // PLOTS_RENDERERS_HEATMAP_CART_H
