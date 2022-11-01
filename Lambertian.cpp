#include "Lambertian.hpp"

Lambertian::Lambertian() {

}

Lambertian::Lambertian(const Lambertian& other) : albedo(other.albedo) {

}

Lambertian::Lambertian(const Color& albedo) : albedo(albedo) {

}

Lambertian::~Lambertian() {

}

Lambertian& Lambertian::operator=(const Lambertian& other) {
  if (&other != this) {
    albedo = other.albedo;
  }
  return *this;
}

bool Lambertian::scatter(
    const Ray& rayIn, const HitRecord& hitRec,
    Color& attenutation, Ray& scattered
) const {
  auto scatteredDirection = hitRec.normal + Vec3::randUnitVec(); 

  // Catch degenerate scatter direction
  if (scatteredDirection.nearZero()) {
    scatteredDirection = hitRec.normal;
  }

  scattered = Ray(hitRec.p, scatteredDirection);
  attenutation = albedo;
  return true;
}
