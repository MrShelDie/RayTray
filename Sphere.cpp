#include <cmath>

#include "Sphere.hpp"

Sphere::Sphere() : radius(0) {

}

Sphere::Sphere(const Sphere& other) :
    center(other.center), radius(other.radius) {
    
}

Sphere::Sphere(Point3 center, float radius) : center(center), radius(radius) {

}

Sphere& Sphere::operator=(const Sphere& other) {
  if (&other != this) {
    center = other.center; 
    radius = other.radius; 
  }
  return *this;  
}

Sphere::~Sphere() {

}

IHittable* Sphere::copy() const {
  return new Sphere;
}

bool Sphere::hit(
    const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
  Vec3  oc = ray.getOrigin() - center;
  float a = ray.getDirection().lengthSquared();
  float halfB = dot(ray.getDirection(), oc);
  float c = oc.lengthSquared() - radius * radius;
  float discriminant = halfB * halfB - a * c;

  if (discriminant < 0) {
    return false;
  }

  float sqrtd = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range
  float root = (-halfB - sqrtd) / a;
  if (root < tMin || root > tMax) {
    root = (-halfB + sqrtd) / a;
    if (root < tMin || root > tMax) {
      return false;
    } 
  }

  hitRecord.t = root;
  hitRecord.p = ray.at(root);
  Vec3 outwardNorm = (hitRecord.p - center) / radius;
  hitRecord.setFaceNorm(ray, outwardNorm);

  return true;
}

const Point3& Sphere::getCenter() const {
  return center;
}

const float&  Sphere::getRadius() const {
  return radius;
}
