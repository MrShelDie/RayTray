#include "RayTray.hpp"
#include "AMaterial.hpp"
#include "HittableList.hpp"

Ray::Ray() {

}

Ray::Ray(const Point3& origin, const Vec3& direction) :
    origin(origin), direction(direction) {

}

Ray::Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction) {

}

Ray::~Ray() {

}

Ray& Ray::operator=(const Ray& ray) {
  if (&ray != this) {
    origin = ray.origin;
    direction = ray.direction;
  }
  return *this;
}

const Point3& Ray::getOrigin() const {
  return origin;
}

const Vec3& Ray::getDirection() const {
  return direction;
}

Point3 Ray::at(const float t) const {
  return origin + direction * t;
}

Color Ray::getColor(const HittableList& world, int depth) const {
  if (depth <= 0) {
    return Color(0, 0, 0);
  }

  HitRecord hitRec;

  if (world.hit(*this, 0.001f, kInfinity, hitRec)) {
    Ray scaterred;
    Color attenutation;
    if (hitRec.material->scatter(*this, hitRec, attenutation, scaterred)) {
      return attenutation * scaterred.getColor(world, depth-1);
    }
    return Color(0, 0, 0);

    auto target = hitRec.p + hitRec.normal + Vec3::randUnitVec();
    auto reflected = Ray(hitRec.p, target - hitRec.p);
    return 0.2f * reflected.getColor(world, depth-1); 
  }
  
  auto unitDirection = direction.toUnitVec();
  float t = 0.5f * (unitDirection.getY() + 1);
  return (1 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1);
}
