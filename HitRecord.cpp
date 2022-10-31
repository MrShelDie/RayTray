#include "HitRecord.hpp"

void HitRecord::setFaceNorm(const Ray& ray, const Vec3& outwardNorm) {
  isFontFace = dot(ray.getDirection(), outwardNorm) < 0;
  norm = isFontFace ? outwardNorm : -outwardNorm;
}
