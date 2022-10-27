#ifndef IHITABLE_H
#define IHITABLE_H

#include "Ray.hpp"

struct HitRecord {
  Point3 p;
  Vec3   norm;
  float  t;
};

class IHittable {
 public:
  virtual bool hit(
      const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
  virtual ~IHittable() {};
};

#endif
