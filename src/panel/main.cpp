#include <iostream>

#include "geometry.h"

int main() {
    constexpr int num_points = 1000;
    std::cout << poflow::get_naca00XX_coords(num_points, 0.5);
}