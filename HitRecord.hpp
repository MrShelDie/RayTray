#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "Ray.hpp"

#include <memory>

using std::shared_ptr;

class AMaterial;

struct HitRecord {
  Point3 p;
  Vec3 norm;
  shared_ptr<AMaterial> material;
  float t;
  bool isFontFace;

  void setFaceNorm(const Ray& ray, const Vec3& outwardNorm);
};

#endif
