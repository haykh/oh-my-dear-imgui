#define IMGUI_DEFINE_MATH_OPERATORS

#include "implot-gpu/implot.h"
#include "implot-gpu/implot_backend.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <implot_internal.h>

namespace omdi::implot {

#define _CAT(x, y)  _CAT_(x, y)
#define _CAT_(x, y) x##y
#define _INSTANTIATE_FOR_NUMERIC_TYPES(chain)                                  \
  _CAT(_INSTANTIATE_FOR_NUMERIC_TYPES_1 chain, _END)
#define _INSTANTIATE_FOR_NUMERIC_TYPES_1(T)                                    \
  INSTANTIATE_MACRO(T) _INSTANTIATE_FOR_NUMERIC_TYPES_2
#define _INSTANTIATE_FOR_NUMERIC_TYPES_2(T)                                    \
  INSTANTIATE_MACRO(T) _INSTANTIATE_FOR_NUMERIC_TYPES_1
#define _INSTANTIATE_FOR_NUMERIC_TYPES_1_END
#define _INSTANTIATE_FOR_NUMERIC_TYPES_2_END
#define CALL_INSTANTIATE_FOR_NUMERIC_TYPES()                                   \
  _INSTANTIATE_FOR_NUMERIC_TYPES(IMPLOT_NUMERIC_TYPES)

#ifdef IMPLOT_CUSTOM_NUMERIC_TYPES
  #define IMPLOT_NUMERIC_TYPES IMPLOT_CUSTOM_NUMERIC_TYPES
#else
  #define IMPLOT_NUMERIC_TYPES                                                 \
    (ImS8)(ImU8)(ImS16)(ImU16)(ImS32)(ImU32)(ImS64)(ImU64)(float)(double)
#endif

#ifndef IMPLOT_NO_FORCE_INLINE
  #ifdef _MSC_VER
    #define IMPLOT_INLINE __forceinline
  #elif defined(__GNUC__)
    #define IMPLOT_INLINE inline __attribute__((__always_inline__))
  #elif defined(__CLANG__)
    #if __has_attribute(__always_inline__)
      #define IMPLOT_INLINE inline __attribute__((__always_inline__))
    #else
      #define IMPLOT_INLINE inline
    #endif
  #else
    #define IMPLOT_INLINE inline
  #endif
#else
  #define IMPLOT_INLINE inline
#endif

  template <typename T>
  struct MaxIdx {
    static const unsigned int Value;
  };

  template <>
  const unsigned int MaxIdx<unsigned short>::Value = 65535;
  template <>
  const unsigned int MaxIdx<unsigned int>::Value = 4294967295;

  struct Transformer1 {
    Transformer1(double          pixMin,
                 double          pltMin,
                 double          pltMax,
                 double          m,
                 double          scaMin,
                 double          scaMax,
                 ImPlotTransform fwd,
                 void*           data)
      : ScaMin(scaMin)
      , ScaMax(scaMax)
      , PltMin(pltMin)
      , PltMax(pltMax)
      , PixMin(pixMin)
      , M(m)
      , TransformFwd(fwd)
      , TransformData(data) {}

    template <typename T>
    IMPLOT_INLINE float operator()(T p) const {
      if (TransformFwd != nullptr) {
        double s = TransformFwd(p, TransformData);
        double t = (s - ScaMin) / (ScaMax - ScaMin);
        p        = PltMin + (PltMax - PltMin) * t;
      }
      return (float)(PixMin + M * (p - PltMin));
    }

    double          ScaMin, ScaMax, PltMin, PltMax, PixMin, M;
    ImPlotTransform TransformFwd;
    void*           TransformData;
  };

  struct Transformer2 {
    Transformer2(const ImPlotAxis& x_axis, const ImPlotAxis& y_axis)
      : Tx(x_axis.PixelMin,
           x_axis.Range.Min,
           x_axis.Range.Max,
           x_axis.ScaleToPixel,
           x_axis.ScaleMin,
           x_axis.ScaleMax,
           x_axis.TransformForward,
           x_axis.TransformData)
      , Ty(y_axis.PixelMin,
           y_axis.Range.Min,
           y_axis.Range.Max,
           y_axis.ScaleToPixel,
           y_axis.ScaleMin,
           y_axis.ScaleMax,
           y_axis.TransformForward,
           y_axis.TransformData) {}

    Transformer2(const ImPlotPlot& plot)
      : Transformer2(plot.Axes[plot.CurrentX], plot.Axes[plot.CurrentY]) {}

    Transformer2() : Transformer2(*GImPlot->CurrentPlot) {}

    template <typename P>
    IMPLOT_INLINE ImVec2 operator()(const P& plt) const {
      ImVec2 out;
      out.x = Tx(plt.x);
      out.y = Ty(plt.y);
      return out;
    }

    template <typename T>
    IMPLOT_INLINE ImVec2 operator()(T x, T y) const {
      ImVec2 out;
      out.x = Tx(x);
      out.y = Ty(y);
      return out;
    }

    Transformer1 Tx;
    Transformer1 Ty;
  };

  struct FitterRect {
    FitterRect(const ImPlotPoint& pmin, const ImPlotPoint& pmax)
      : Pmin(pmin)
      , Pmax(pmax) {}

    FitterRect(const ImPlotRect& rect) : FitterRect(rect.Min(), rect.Max()) {}

    void Fit(ImPlotAxis& x_axis, ImPlotAxis& y_axis) const {
      x_axis.ExtendFitWith(y_axis, Pmin.x, Pmin.y);
      y_axis.ExtendFitWith(x_axis, Pmin.y, Pmin.x);
      x_axis.ExtendFitWith(y_axis, Pmax.x, Pmax.y);
      y_axis.ExtendFitWith(x_axis, Pmax.y, Pmax.x);
    }

    const ImPlotPoint Pmin;
    const ImPlotPoint Pmax;
  };

  struct RendererBase {
    RendererBase(int prims, int idx_consumed, int vtx_consumed)
      : Prims(prims)
      , IdxConsumed(idx_consumed)
      , VtxConsumed(vtx_consumed) {}

    const int    Prims;
    Transformer2 Transformer;
    const int    IdxConsumed;
    const int    VtxConsumed;
  };

  struct RectC {
    ImPlotPoint Pos;
    ImPlotPoint HalfSize;
    ImU32       Color;
  };

  IMPLOT_INLINE void PrimRectFill(ImDrawList&   draw_list,
                                  const ImVec2& Pmin,
                                  const ImVec2& Pmax,
                                  ImU32         col,
                                  const ImVec2& uv) {
    draw_list._VtxWritePtr[0].pos    = Pmin;
    draw_list._VtxWritePtr[0].uv     = uv;
    draw_list._VtxWritePtr[0].col    = col;
    draw_list._VtxWritePtr[1].pos    = Pmax;
    draw_list._VtxWritePtr[1].uv     = uv;
    draw_list._VtxWritePtr[1].col    = col;
    draw_list._VtxWritePtr[2].pos.x  = Pmin.x;
    draw_list._VtxWritePtr[2].pos.y  = Pmax.y;
    draw_list._VtxWritePtr[2].uv     = uv;
    draw_list._VtxWritePtr[2].col    = col;
    draw_list._VtxWritePtr[3].pos.x  = Pmax.x;
    draw_list._VtxWritePtr[3].pos.y  = Pmin.y;
    draw_list._VtxWritePtr[3].uv     = uv;
    draw_list._VtxWritePtr[3].col    = col;
    draw_list._VtxWritePtr          += 4;
    draw_list._IdxWritePtr[0]        = (ImDrawIdx)(draw_list._VtxCurrentIdx);
    draw_list._IdxWritePtr[1]  = (ImDrawIdx)(draw_list._VtxCurrentIdx + 1);
    draw_list._IdxWritePtr[2]  = (ImDrawIdx)(draw_list._VtxCurrentIdx + 2);
    draw_list._IdxWritePtr[3]  = (ImDrawIdx)(draw_list._VtxCurrentIdx);
    draw_list._IdxWritePtr[4]  = (ImDrawIdx)(draw_list._VtxCurrentIdx + 1);
    draw_list._IdxWritePtr[5]  = (ImDrawIdx)(draw_list._VtxCurrentIdx + 3);
    draw_list._IdxWritePtr    += 6;
    draw_list._VtxCurrentIdx  += 4;
  }

  template <typename _Getter>
  struct RendererRectC : RendererBase {
    RendererRectC(const _Getter& getter)
      : RendererBase(getter.Count, 6, 4)
      , Getter(getter) {}

    void Init(ImDrawList& draw_list) const {
      UV = draw_list._Data->TexUvWhitePixel;
    }

    IMPLOT_INLINE bool Render(ImDrawList&   draw_list,
                              const ImRect& cull_rect,
                              int           prim) const {
      RectC  rect = Getter(prim);
      ImVec2 P1   = this->Transformer(rect.Pos.x - rect.HalfSize.x,
                                    rect.Pos.y - rect.HalfSize.y);
      ImVec2 P2   = this->Transformer(rect.Pos.x + rect.HalfSize.x,
                                    rect.Pos.y + rect.HalfSize.y);
      if ((rect.Color & IM_COL32_A_MASK) == 0 ||
          !cull_rect.Overlaps(ImRect(ImMin(P1, P2), ImMax(P1, P2)))) {
        return false;
      }
      PrimRectFill(draw_list, P1, P2, rect.Color, UV);
      return true;
    }

    const _Getter& Getter;
    mutable ImVec2 UV;
  };

  template <typename T>
  struct GetterHeatmapRowMaj {
    GetterHeatmapRowMaj(const T* values,
                        int      rows,
                        int      cols,
                        double   scale_min,
                        double   scale_max,
                        double   width,
                        double   height,
                        double   xref,
                        double   yref,
                        double   ydir)
      : Values(values)
      , Count(rows * cols)
      , Rows(rows)
      , Cols(cols)
      , ScaleMin(scale_min)
      , ScaleMax(scale_max)
      , Width(width)
      , Height(height)
      , XRef(xref)
      , YRef(yref)
      , YDir(ydir)
      , HalfSize(Width * 0.5, Height * 0.5) {}

    template <typename I>
    IMPLOT_INLINE RectC operator()(I idx) const {
      double            val = (double)Values[idx];
      const int         r   = idx / Cols;
      const int         c   = idx % Cols;
      const ImPlotPoint p(XRef + HalfSize.x + c * Width,
                          YRef + YDir * (HalfSize.y + r * Height));
      RectC             rect;
      rect.Pos      = p;
      rect.HalfSize = HalfSize;
      const float t = ImClamp((float)ImRemap01(val, ScaleMin, ScaleMax), 0.0f, 1.0f);
      ImPlotContext& gp = *GImPlot;
      rect.Color        = gp.ColormapData.LerpTable(gp.Style.Colormap, t);
      return rect;
    }

    const T* const    Values;
    const int         Count, Rows, Cols;
    const double      ScaleMin, ScaleMax, Width, Height, XRef, YRef, YDir;
    const ImPlotPoint HalfSize;
  };

  template <typename T>
  struct GetterHeatmapColMaj {
    GetterHeatmapColMaj(const T* values,
                        int      rows,
                        int      cols,
                        double   scale_min,
                        double   scale_max,
                        double   width,
                        double   height,
                        double   xref,
                        double   yref,
                        double   ydir)
      : Values(values)
      , Count(rows * cols)
      , Rows(rows)
      , Cols(cols)
      , ScaleMin(scale_min)
      , ScaleMax(scale_max)
      , Width(width)
      , Height(height)
      , XRef(xref)
      , YRef(yref)
      , YDir(ydir)
      , HalfSize(Width * 0.5, Height * 0.5) {}

    template <typename I>
    IMPLOT_INLINE RectC operator()(I idx) const {
      double            val = (double)Values[idx];
      const int         r   = idx % Rows;
      const int         c   = idx / Rows;
      const ImPlotPoint p(XRef + HalfSize.x + c * Width,
                          YRef + YDir * (HalfSize.y + r * Height));
      RectC             rect;
      rect.Pos      = p;
      rect.HalfSize = HalfSize;
      const float t = ImClamp((float)ImRemap01(val, ScaleMin, ScaleMax), 0.0f, 1.0f);
      ImPlotContext& gp = *GImPlot;
      rect.Color        = gp.ColormapData.LerpTable(gp.Style.Colormap, t);
      return rect;
    }

    const T* const    Values;
    const int         Count, Rows, Cols;
    const double      ScaleMin, ScaleMax, Width, Height, XRef, YRef, YDir;
    const ImPlotPoint HalfSize;
  };

  template <class _Renderer>
  void RenderPrimitivesEx(const _Renderer& renderer,
                          ImDrawList&      draw_list,
                          const ImRect&    cull_rect) {
    unsigned int prims        = renderer.Prims;
    unsigned int prims_culled = 0;
    unsigned int idx          = 0;
    renderer.Init(draw_list);
    while (prims) {
      // find how many can be reserved up to end of current draw command's limit
      unsigned int cnt = ImMin(prims,
                               (MaxIdx<ImDrawIdx>::Value - draw_list._VtxCurrentIdx) /
                                 renderer.VtxConsumed);
      // make sure at least this many elements can be rendered to avoid situations
      // where at the end of buffer this slow path is not taken all the time
      if (cnt >= ImMin(64u, prims)) {
        if (prims_culled >= cnt) {
          prims_culled -= cnt; // reuse previous reservation
        } else {
          // add more elements to previous reservation
          draw_list.PrimReserve((cnt - prims_culled) * renderer.IdxConsumed,
                                (cnt - prims_culled) * renderer.VtxConsumed);
          prims_culled = 0;
        }
      } else {
        if (prims_culled > 0) {
          draw_list.PrimUnreserve(prims_culled * renderer.IdxConsumed,
                                  prims_culled * renderer.VtxConsumed);
          prims_culled = 0;
        }
        cnt = ImMin(prims,
                    (MaxIdx<ImDrawIdx>::Value - 0 /*draw_list._VtxCurrentIdx*/) /
                      renderer.VtxConsumed);
        // reserve new draw command
        draw_list.PrimReserve(cnt * renderer.IdxConsumed,
                              cnt * renderer.VtxConsumed);
      }
      prims -= cnt;
      for (unsigned int ie = idx + cnt; idx != ie; ++idx) {
        if (!renderer.Render(draw_list, cull_rect, idx)) {
          prims_culled++;
        }
      }
    }
    if (prims_culled > 0) {
      draw_list.PrimUnreserve(prims_culled * renderer.IdxConsumed,
                              prims_culled * renderer.VtxConsumed);
    }
  }

  template <template <class> class _Renderer, class _Getter, typename... Args>
  void RenderPrimitives1(const _Getter& getter, Args... args) {
    ImDrawList&   draw_list = *ImPlot::GetPlotDrawList();
    const ImRect& cull_rect = ImPlot::GetCurrentPlot()->PlotRect;
    RenderPrimitivesEx(_Renderer<_Getter>(getter, args...), draw_list, cull_rect);
  }

  template <typename T>
  struct ImGuiDataTypeGetter {
    static const ImGuiDataType Value;
  };

  template <>
  const ImGuiDataType ImGuiDataTypeGetter<float>::Value = ImGuiDataType_Float;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<double>::Value = ImGuiDataType_Double;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImU8>::Value = ImGuiDataType_U8;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImS8>::Value = ImGuiDataType_S8;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImU16>::Value = ImGuiDataType_U16;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImS16>::Value = ImGuiDataType_S16;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImU32>::Value = ImGuiDataType_U32;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImS32>::Value = ImGuiDataType_S32;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImU64>::Value = ImGuiDataType_U64;
  template <>
  const ImGuiDataType ImGuiDataTypeGetter<ImS64>::Value = ImGuiDataType_S64;

  template <typename T>
  void RenderHeatmap(ImDrawList&        draw_list,
                     const T*           values,
                     int                rows,
                     int                cols,
                     double             scale_min,
                     double             scale_max,
                     const ImPlotPoint& bounds_min,
                     const ImPlotPoint& bounds_max,
                     bool               reverse_y,
                     bool               col_maj) {
    ImPlotWrapperContext& gp = *GImPlotWrapper;
    Transformer2          transformer;
    if (scale_min == 0 && scale_max == 0) {
      T temp_min, temp_max;
      ImMinMaxArray(values, rows * cols, &temp_min, &temp_max);
      scale_min = (double)temp_min;
      scale_max = (double)temp_max;
    }
    if (scale_min == scale_max) {
      ImVec2 a   = transformer(bounds_min);
      ImVec2 b   = transformer(bounds_max);
      ImU32  col = ImPlot::GetColormapColorU32(0, gp.Style.Colormap);
      draw_list.AddRectFilled(a, b, col);
      return;
    }
    // const double yref = reverse_y ? bounds_max.y : bounds_min.y;
    // const double ydir = reverse_y ? -1 : 1;
    // if (col_maj) {
    //   GetterHeatmapColMaj<T> getter(values,
    //                                 rows,
    //                                 cols,
    //                                 scale_min,
    //                                 scale_max,
    //                                 (bounds_max.x - bounds_min.x) / cols,
    //                                 (bounds_max.y - bounds_min.y) / rows,
    //                                 bounds_min.x,
    //                                 yref,
    //                                 ydir);
    //   RenderPrimitives1<RendererRectC>(getter);
    // } else {
    //   GetterHeatmapRowMaj<T> getter(values,
    //                                 rows,
    //                                 cols,
    //                                 scale_min,
    //                                 scale_max,
    //                                 (bounds_max.x - bounds_min.x) / cols,
    //                                 (bounds_max.y - bounds_min.y) / rows,
    //                                 bounds_min.x,
    //                                 yref,
    //                                 ydir);
    //   RenderPrimitives1<RendererRectC>(getter);
    // }
    ImVec2 bmin = transformer(bounds_min);
    ImVec2 bmax = transformer(bounds_max);

    ImPlot::Backend::RenderHeatmap(gp.CurrentItem->ID,
                                   values,
                                   ImGuiDataTypeGetter<T>::Value,
                                   rows,
                                   cols,
                                   (float)scale_min,
                                   (float)scale_max,
                                   bmin,
                                   bmax,
                                   bounds_min,
                                   bounds_max,
                                   ImPlotScale_Linear,
                                   reverse_y,
                                   gp.Style.Colormap,
                                   draw_list);
  }

  template <typename T>
  void PlotHeatmap(const char*        label_id,
                   const T*           values,
                   int                rows,
                   int                cols,
                   double             scale_min,
                   double             scale_max,
                   const ImPlotPoint& bounds_min,
                   const ImPlotPoint& bounds_max,
                   ImPlotHeatmapFlags flags) {
    if (ImPlot::BeginItemEx(label_id, FitterRect(bounds_min, bounds_max))) {
      if (rows <= 0 || cols <= 0) {
        ImPlot::EndItem();
        return;
      }
      ImDrawList& draw_list = *ImPlot::GetPlotDrawList();
      const bool  col_maj   = ImHasFlag(flags, ImPlotHeatmapFlags_ColMajor);
      RenderHeatmap(draw_list,
                    values,
                    rows,
                    cols,
                    scale_min,
                    scale_max,
                    bounds_min,
                    bounds_max,
                    true,
                    col_maj);
      ImPlot::EndItem();
    }
  }

#define INSTANTIATE_MACRO(T)                                                   \
  template IMPLOT_API void PlotHeatmap<T>(const char*        label_id,         \
                                          const T*           values,           \
                                          int                rows,             \
                                          int                cols,             \
                                          double             scale_min,        \
                                          double             scale_max,        \
                                          const ImPlotPoint& bounds_min,       \
                                          const ImPlotPoint& bounds_max,       \
                                          ImPlotHeatmapFlags flags);
  CALL_INSTANTIATE_FOR_NUMERIC_TYPES()
#undef INSTANTIATE_MACRO

} // namespace omdi::implot