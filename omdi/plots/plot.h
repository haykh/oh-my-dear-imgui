#ifndef PLOTS_PLOT_H
#define PLOTS_PLOT_H

#include <implot.h>

#include <map>
#include <string>

namespace omdi::plots {

  /**
   * @brief Abstract base class for different types of plots.
   */
  class Plot {
  protected:
    std::string m_label { "GenericPlot" };

  public:
    Plot(const std::string& label = "GenericPlot") : m_label { label } {}

    virtual void plot() = 0;

    auto label() const -> const std::string& {
      return m_label;
    }
  };

  /**
   * @brief Base class for different types data container used for plotting.
   */
  template <typename T>
  class DataPlot {
  protected:
    std::map<std::string, const T* const> m_data;
    std::map<std::string, ImPlotSpec>     m_specs;

  public:
    auto set_spec(const std::string& label, const ImPlotSpec& spec) -> void {
      m_specs[label] = spec;
    }

    auto get_spec(const std::string& label) const -> ImPlotSpec {
      auto it = m_specs.find(label);
      if (it != m_specs.end()) {
        return it->second;
      }
      return ImPlotSpec();
    }

    DataPlot(const std::map<std::string, const T* const>& data = {})
      : m_data { data } {}
  };

} // namespace omdi::plots

#endif // PLOTS_PLOT_H
