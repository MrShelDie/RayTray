#ifndef AMATERIAL_H
#define AMATERIAL_H

#include "Ray.hpp"

struct HitRecord;

class AMaterial {
 public:
  virtual ~AMaterial() {};

  virtual bool scatter(
    const Ray& rayIn, const HitRecord& hitRec,
    Color& attenutation, Ray& scattere
  ) const = 0;
};

#endif
