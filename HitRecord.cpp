#include "HitRecord.hpp"

void HitRecord::setFaceNorm(const Ray& ray, const Vec3& outwardNorm) {
  isFontFace = Vec3::dot(ray.getDirection(), outwardNorm) < 0;
  normal = isFontFace ? outwardNorm : -outwardNorm;
}
