#ifndef AMATERIAL_H
#define AMATERIAL_H

#include "Ray.hpp"
#include "HitRecord.hpp"

class AMaterial {
 public:
  virtual ~AMaterial() {};

  virtual bool scatter(
    const Ray& rayIn, const HitRecord& hitRec,
    Color& attenutation, Ray& scattered
  ) const = 0;
};

#endif
