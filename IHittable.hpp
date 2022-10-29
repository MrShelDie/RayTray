#ifndef IHITABLE_H
#define IHITABLE_H

#include "Ray.hpp"

struct HitRecord {
  Point3 p;
  Vec3   norm;
  float  t;
  bool   isFontFace;

  void setFaceNorm(const Ray& ray, const Vec3& outwardNorm) {
    isFontFace = dot(ray.getDirection(), outwardNorm) < 0;
    norm = isFontFace ? outwardNorm : -outwardNorm;
  }
};

class IHittable {
 public:
  virtual bool hit(
      const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
  virtual IHittable* copy() const = 0;
  virtual ~IHittable() {};
};

#endif
