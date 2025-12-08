#ifndef IMPLOT_GPU_PLOTTERS_H
#define IMPLOT_GPU_PLOTTERS_H

#include <implot.h>

namespace omdi::implot {

  template <typename T>
  void PlotHeatmap(const char*        label_id,
                   const T*           values,
                   int                rows,
                   int                cols,
                   double             scale_min  = 0,
                   double             scale_max  = 0,
                   const ImPlotPoint& bounds_min = ImPlotPoint(0, 0),
                   const ImPlotPoint& bounds_max = ImPlotPoint(1, 1),
                   ImPlotHeatmapFlags flags      = 0);

} // namespace omdi::implot

#endif // IMPLOT_GPU_PLOTTERS_H