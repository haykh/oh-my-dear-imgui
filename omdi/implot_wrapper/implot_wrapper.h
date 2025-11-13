#ifndef IMPLOT_WRAPPER_IMPLOT_WRAPPER_H
#define IMPLOT_WRAPPER_IMPLOT_WRAPPER_H

#include <imgui.h>
#include <implot.h>
#include <implot_internal.h>

namespace omdi::implot {

  struct ImPlotWrapperContext : ImPlotContext {
    void* backendCtx;
  };

#ifndef GImPlotWrapper
  extern IMPLOT_API ImPlotWrapperContext* GImPlotWrapper;
#endif

  auto CreateContext() -> ImPlotWrapperContext*;

  void DestroyContext(ImPlotWrapperContext* = nullptr);

} // namespace omdi::implot

#endif // IMPLOT_WRAPPER_IMPLOT_WRAPPER_H
