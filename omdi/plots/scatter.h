#ifndef PLOTS_SCATTER_H
#define PLOTS_SCATTER_H

#include "plots/containers.h"
#include "plots/plot.h"

#include <map>
#include <string>

namespace omdi::plots {

  struct ScatterPlot : public Plot {
    bool        aspect_equal = true;
    std::string label        = "ScatterPlot";

    std::map<std::string, const Points* const> data;

    ScatterPlot(const std::map<std::string, const Points* const>& data,
                const std::string& label        = "ScatterPlot",
                bool               aspect_equal = true)
      : data { data }
      , aspect_equal { aspect_equal }
      , label { label } {}

    void plot() override;
  };

}; // namespace omdi::plots

#endif // PLOTS_SCATTER_H
