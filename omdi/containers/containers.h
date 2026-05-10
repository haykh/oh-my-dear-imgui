#ifndef CONTAINERS_CONTAINERS_H
#define CONTAINERS_CONTAINERS_H

#include <cstddef>
#include <vector>

namespace omdi {

  /**
   * @brief Structure to hold 2D scattered points data.
   */
  struct Points {
    std::vector<float> x, y;
    size_t             npoints;

    Points(const std::vector<float>& x, const std::vector<float>& y, size_t npoints)
      : x { x }
      , y { y }
      , npoints { npoints } {}
  };

  /**
   * @brief Structure to hold 2D grid data.
   */
  struct GridXY {
    std::vector<float> x, y;
    size_t             nx;
    size_t             ny;
    std::vector<float> z;

    GridXY(const std::vector<float>& x,
           const std::vector<float>& y,
           size_t                    nx,
           size_t                    ny,
           const std::vector<float>& z)
      : x { x }
      , y { y }
      , nx { nx }
      , ny { ny }
      , z { z } {}
  };

} // namespace omdi

#endif // CONTAINERS_CONTAINERS_H
