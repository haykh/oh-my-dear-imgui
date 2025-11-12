#ifndef PLOTS_PLOT_H
#define PLOTS_PLOT_H

namespace omdi::plots {

  struct Plot {
    virtual void plot() = 0;
  };

} // namespace omdi::plots

#endif // PLOTS_PLOT_H
