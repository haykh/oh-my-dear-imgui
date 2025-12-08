#ifndef EXAMPLES_SIM_H
#define EXAMPLES_SIM_H

namespace omdi::examples {

  struct Sim {
    virtual void update(double time, double delta) = 0;
  };

} // namespace omdi::examples

#endif // EXAMPLES_SIM_H