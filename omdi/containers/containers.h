#ifndef CONTAINERS_CONTAINERS_H
#define CONTAINERS_CONTAINERS_H

#include <cstddef>

namespace omdi {

  /**
   * @brief Structure to hold 2D scattered points data.
   */
  struct Points {
    const float* const x;
    const float* const y;
    std::size_t        npoints;

    Points(const float* x, const float* y, std::size_t npoints)
      : x { x }
      , y { y }
      , npoints { npoints } {}
  };

  /**
   * @brief Structure to hold 2D grid data.
   */
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

} // namespace omdi

#endif // CONTAINERS_CONTAINERS_H
