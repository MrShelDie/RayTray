#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "AMaterial.hpp"

class Lambertian : public AMaterial {
 public:
  Lambertian();
  Lambertian(const Lambertian& other);
  Lambertian(const Color& albedo);
  ~Lambertian();

  Lambertian& operator=(const Lambertian& other);

  virtual bool scatter(
    const Ray& rayIn, const HitRecord& hitRec,
    Color& attenutation, Ray& scattered
  ) const override;

 private:
  Color albedo;
};

#endif
