#include "Ray.hpp"

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
