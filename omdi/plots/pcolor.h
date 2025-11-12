#ifndef PLOTS_PCOLOR_H
#define PLOTS_PCOLOR_H

#include "plots/containers.h"
#include "plots/plot.h"

#include <map>
#include <string>

namespace omdi::plots {

  struct PcolorPlot : public Plot {
    bool        aspect_equal = true;
    std::string label        = "PcolorPlot";
    int         which        = 0;

    std::map<std::string, const GridXY* const> data;

    PcolorPlot(const std::map<std::string, const GridXY* const>& data,
               const std::string& label        = "PcolorPlot",
               bool               aspect_equal = true)
      : data { data }
      , aspect_equal { aspect_equal }
      , label { label } {}

    void plot() override;
  };

} // namespace omdi::plots

#endif // PLOTS_PCOLOR_H
