//
// Created by Krrish Kishore Kumar on 7/25/25.
//

#ifndef CONSTS_H
#define CONSTS_H
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * (pi / 180.0);
}
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}
#include "color.h"
#include "ray.h"
#include "interval.h"
#include "vec3.h"
#endif //CONSTS_H
