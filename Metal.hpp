#ifndef METAL_H
#define METAL_H

#include "AMaterial.hpp"

class Metal : public AMaterial {
 public:
  Metal();
  Metal(const Metal& m);
  Metal(const Color& albedo);
  ~Metal();

  Metal& operator=(const Metal& m);

  bool scatter(
    const Ray& rayIn, const HitRecord& hitRec,
    Color& attenutation, Ray& scattered
  ) const override;

 private:
  Color albedo;
};

#endif
