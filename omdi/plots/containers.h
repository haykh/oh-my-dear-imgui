#ifndef PLOTS_CONTAINERS_H
#define PLOTS_CONTAINERS_H

#include <cstddef>

namespace omdi::plots {

  struct Points {
    const float* const x;
    const float* const y;
    std::size_t        npoints;

    Points(const float* x, const float* y, std::size_t npoints)
      : x { x }
      , y { y }
      , npoints { npoints } {}
  };

  struct GridXY {
    const float* const x;
    const float* const y;
    std::size_t        nx;
    std::size_t        ny;
    const float* const z;

    GridXY(const float* x, const float* y, std::size_t nx, std::size_t ny, const float* z)
      : x { x }
      , y { y }
      , nx { nx }
      , ny { ny }
      , z { z } {}
  };

} // namespace omdi::plots

#endif // PLOTS_CONTAINERS_H
