#ifndef RAY_H
#define RAY_H

#include "Vec3.hpp"

class HittableList;

class Ray {
 public:
  Ray();
  Ray(const Point3& origin, const Vec3& direction);
  Ray(const Ray& ray);
  ~Ray();

  Ray& operator=(const Ray& ray);

  const Point3& getOrigin() const;
  const Vec3&   getDirection() const;

  Color   getColor(const HittableList& world, int depth) const;

  Point3 at(const float t) const;

 private:
  Point3 origin;
  Vec3   direction;
};

#endif
