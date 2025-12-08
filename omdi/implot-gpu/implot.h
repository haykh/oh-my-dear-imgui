#ifndef IMPLOT_GPU_IMPLOT_H
#define IMPLOT_GPU_IMPLOT_H

#include <implot.h>
#include <implot_internal.h>

namespace omdi::implot {

  struct ImPlotWrapperContext : ImPlotContext {
    void* backendCtx;
  };

#ifndef GImPlotWrapper
  extern IMPLOT_API ImPlotWrapperContext* GImPlotWrapper;
#endif

  auto Init() -> ImPlotWrapperContext*;
  void Destroy(ImPlotWrapperContext* = nullptr);
  auto CreateContext() -> ImPlotWrapperContext*;
  void DestroyContext(ImPlotWrapperContext* = nullptr);
  void RegisterAllColormaps();

  void BustItemCache();
  void BustColorCache(const char*);

} // namespace omdi::implot

#endif // IMPLOT_GPU_IMPLOT_H