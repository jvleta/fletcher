#include "geometry.h"

#include <iostream>

#include "json.hpp"

namespace poflow {

nlohmann::json coordinates_to_json(const Coordinates& coords) {
    nlohmann::json j;
    j["x"] = coords.xcoords;
    j["y"] = coords.ycoords;
    return j;
}
Coordinates get_ellipse_coords(int num_points, double ratio) {
  std::vector<double> xcoords(num_points);
  std::vector<double> ycoords(num_points);
  int num_elements = num_points - 1;
  int num_elements_per_size = num_elements / 2;
  double dtheta = M_PI / static_cast<double>(num_elements_per_size);

  for (int i = 0; i < num_elements_per_size + 1; ++i) {
    double theta = i * dtheta;
    theta = M_PI - theta;
    xcoords[i] = std::cos(theta);
    ycoords[i] = ratio * std::sin(theta);
  }

  // Refelct the y coords in the lower half.
  for (int i = num_elements_per_size + 1; i < num_elements; ++i) {
    xcoords[i] = xcoords[num_elements - i];
    ycoords[i] = -ycoords[num_elements - i];
  }

  xcoords[num_points - 1] = xcoords[0];
  ycoords[num_points - 1] = ycoords[0];
  return Coordinates(xcoords, ycoords);
}

Coordinates get_naca00XX_coords(int num_points, double ratio) {
  std::vector<double> xcoords(num_points);
  std::vector<double> ycoords(num_points);

  int num_elements = num_points - 1;
  int num_elements_per_side = num_elements / 2;
  double dtheta = M_PI / static_cast<double>(num_elements_per_side);

  auto compute_half_thickness = [](double x, double t) {
    // TODO: Use compiler explorer to learn about the
    // effects of using constexpr here.
    constexpr double a0 = 5.0;
    constexpr double a1 = 0.2969;
    constexpr double a2 = -0.1260;
    constexpr double a3 = -0.3516;
    constexpr double a4 = 0.2843;
    constexpr double a5 = -0.1015;
    return a0 * t *
           (a1 * std::sqrt(x) + a2 * x + a3 * std::pow(x, 2.0) +
            a4 * std::pow(x, 3.0) + a5 * std::pow(x, 4.0));
  };
  auto dx = 1.0 / num_elements_per_side;
  for (int i = 0; i < num_elements_per_side + 1; ++i) {
    xcoords[i] = i * dx;
    ycoords[i] = compute_half_thickness(xcoords[i], ratio);
  }
  // Refelct the y coords in the lower half.
  for (int i = num_elements_per_side + 1; i < num_elements; ++i) {
    xcoords[i] = xcoords[num_elements - i];
    ycoords[i] = -ycoords[num_elements - i];
  }
  xcoords[num_points - 1] = xcoords[0];
  ycoords[num_points - 1] = ycoords[0];

  return Coordinates(xcoords, ycoords);
}

} // namespace poflow

extern "C" {

const char* GetEllipseCoordinates(int num_points, double ratio) {
  auto coords = poflow::get_ellipse_coords(num_points, ratio);
  auto json = poflow::coordinates_to_json(coords);
  return std::move(json.dump().c_str());
}

const char* GetNaca00XXCoordinates(int num_points, double ratio) {
  auto coords = poflow::get_naca00XX_coords(num_points, ratio);
  auto json = poflow::coordinates_to_json(coords);
  return std::move(json.dump().c_str());
}

}