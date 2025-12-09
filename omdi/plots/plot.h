#ifndef PLOTS_PLOT_H
#define PLOTS_PLOT_H

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

} // namespace omdi::plots

#endif // PLOTS_PLOT_H
