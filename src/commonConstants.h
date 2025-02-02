#ifndef COMMON_CONSTANTS_H
#define COMMON_CONSTANTS_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();

const double pi = 3.1415926535897932385;

inline double degree_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double randomDouble() {
	return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
	return min + (max - min) * randomDouble();
}

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"


#endif // !COMMON_CONSTANTS_H
