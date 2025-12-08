#include "implot-gpu/implot.h"
#include "implot-gpu/implot_backend.h"

#include "utils.h"

namespace omdi::implot {

#ifndef GImPlotWrapper
  ImPlotWrapperContext* GImPlotWrapper = nullptr;
#endif

  auto Init() -> ImPlotWrapperContext* {
    auto ctx = CreateContext();
    RegisterAllColormaps();
    return ctx;
  }

  void Destroy(ImPlotWrapperContext* ctx) {
    DestroyContext(ctx);
  }

  auto CreateContext() -> ImPlotWrapperContext* {
    auto ctx        = IM_NEW(ImPlotWrapperContext)();
    ctx->backendCtx = ImPlot::Backend::CreateContext();
    ImPlot::Initialize(ctx);
    if (GImPlotWrapper == nullptr) {
      ImPlot::SetCurrentContext(ctx);
      GImPlotWrapper = ctx;
    }
    omdi::logger::Debug("ImPlot context created.");
    return ctx;
  }

  void DestroyContext(ImPlotWrapperContext* ctx) {
    ImPlot::Backend::DestroyContext();
    if (ctx == nullptr) {
      ctx = GImPlotWrapper;
    }
    if (GImPlotWrapper == ctx) {
      ImPlot::SetCurrentContext(nullptr);
      GImPlotWrapper = nullptr;
    }
    IM_DELETE(ctx);
    omdi::logger::Debug("ImPlot context destroyed.");
  }

  void RegisterAllColormaps() {
    if (omdi::implot::GImPlotWrapper == nullptr) {
      return;
    }
    ImPlot::SetCurrentContext(omdi::implot::GImPlotWrapper);
    for (auto cm = 0; cm < ImPlot::GetColormapCount(); ++cm) {
      const auto cmap_size = ImPlot::GetColormapSize(cm);
      auto       colormap  = new ImU32[cmap_size];
      for (int i = 0; i < cmap_size; i++) {
        colormap[i] = ImPlot::GetColormapColorU32(i, cm);
      }
      ImPlot::Backend::AddColormap(colormap, cmap_size, false);
    }
    omdi::logger::Debug("Colormaps registered with an ImPlot backend.");
  }

  void BustItemCache() {
    ImPlotWrapperContext& gp = *GImPlotWrapper;
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
    ImPlotWrapperContext& gp = *GImPlotWrapper;
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

} // namespace omdi::implot