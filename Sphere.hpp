#ifndef SPHERE_H
#define SPHERE_H

#include "IHittable.hpp"

class Sphere : public IHittable {
 public:
  Sphere();
  Sphere(const Sphere& other);
  Sphere(Point3 center, float radius);
  
  Sphere& operator=(const Sphere& other);

  virtual ~Sphere();
  virtual bool hit(const Ray& ray, float tMin,
                   float tMax, HitRecord& hitRecord) const override;

  const Point3& getCenter() const;
  const float&  getRadius() const;

 private:
  Point3 center;
  float  radius;
};

#endif
