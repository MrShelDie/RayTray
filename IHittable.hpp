#ifndef IHITABLE_H
#define IHITABLE_H

#include "Ray.hpp"
#include "HitRecord.hpp"

class IHittable {
 public:
  virtual ~IHittable() {};

  virtual IHittable* copy() const = 0;

  virtual bool hit(
    const Ray& ray, float tMin,
    float tMax, HitRecord& HitRecord
  ) const = 0;
};

#endif
