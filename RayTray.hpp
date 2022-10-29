#ifndef RAY_TRAY_H
#define RAY_TRAY_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Common Headers
#include "Vec3.hpp"
#include "Ray.hpp"

// Numeric
const float kInfinity = std::numeric_limits<float>::infinity();
const float kPi = 3.1415926535897932385;
const int   kSamplesPerPixel = 100;

// Utility Functions
float deg2rad(float degrees);
float randFloat();
float randFloat(float min, float max);
float clamp(float x, float min, float max);

#endif
