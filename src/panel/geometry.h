#pragma once

#include <cmath>
#include <ostream>
#include <vector>

namespace poflow {

struct Coordinates {
  int num_points = 0;
  std::vector<double> xcoords;
  std::vector<double> ycoords;
  Coordinates(const std::vector<double> &x, const std::vector<double> &y) {
    num_points = x.size();
    xcoords = x;
    ycoords = y;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Coordinates &coordinates) {
    for (int i = 0; i < coordinates.num_points; ++i) {
      os << coordinates.xcoords[i] << "," << coordinates.ycoords[i] << "\n";
    }
    return os;
  }
};

Coordinates get_ellipse_coords(int num_points, double ratio);
Coordinates get_naca00XX_coords(int num_points, double ratio);

}; // namespace poflow