#include "implot_wrapper/implot_backend.h"
#include "implot_wrapper/implot_wrapper.h"

#include <implot.h>
#include <implot_internal.h>

namespace omdi::implot {

#ifndef GImPlotWrapper
  ImPlotWrapperContext* GImPlotWrapper = nullptr;
#endif

  auto CreateContext() -> ImPlotWrapperContext* {
    auto ctx        = IM_NEW(ImPlotWrapperContext)();
    ctx->backendCtx = ImPlot::Backend::CreateContext();
    ImPlot::Initialize(ctx);
    if (GImPlotWrapper == nullptr) {
      ImPlot::SetCurrentContext(ctx);
    }
    return ctx;
  }

  void DestroyContext(ImPlotWrapperContext* ctx) {
    ImPlot::Backend::DestroyContext();
    if (ctx == nullptr) {
      ctx = GImPlotWrapper;
    }
    if (GImPlotWrapper == ctx) {
      ImPlot::SetCurrentContext(nullptr);
    }
    IM_DELETE(ctx);
  }

} // namespace omdi::implot
