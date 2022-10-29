#include "RayTray.hpp"

float deg2rad(float degrees) {
  return degrees * kPi / 180.0f;
}

// Returns a random real in [0,1)
float randFloat() {
  return rand() / (RAND_MAX + 1.0f);
}

// Returns a random real in [min,max)
float randFloat(float min, float max) {
  return min + (max - min) * randFloat();
}

float clamp(float x, float min, float max) {
  if (x < min)
    return min;
  if (x > max)
     return max;
  return x;
}
