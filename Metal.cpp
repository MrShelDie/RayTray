#include "Metal.hpp"

Metal::Metal() {

}

Metal::Metal(const Metal& m) : albedo(m.albedo) {

}

Metal::Metal(const Color& albedo) : albedo(albedo) {

}

Metal::~Metal() {

}

Metal& Metal::operator=(const Metal& m) {
  if (&m != this) {
    albedo = m.albedo;
  }
  return *this;
}

bool Metal::scatter(
  const Ray& rayIn, const HitRecord& hitRec,
  Color& attenutation, Ray& scattered
) const {
  auto reflectedDirection = Vec3::reflect(
    rayIn.getDirection().toUnitVec(), hitRec.normal
  );
  scattered = Ray(hitRec.p, reflectedDirection);
  attenutation = albedo;
  return Vec3::dot(scattered.getDirection(), hitRec.normal) > 0;
}
