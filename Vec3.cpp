#include <cmath>

#include "Vec3.hpp"

Vec3::Vec3() : x(0), y(0), z(0) {

}

Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {

}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {

}

Vec3::~Vec3() {

}

Vec3& Vec3::operator=(const Vec3& v) {
  if (&v != this) {
    x = v.x;
    y = v.y;
    z = v.z;
  }
  return *this;
}

Vec3& Vec3::operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
  return *this;
}

Vec3& Vec3::operator*=(const float t) {
    x *= t;
    y *= t;
    z *= t;
  return *this; 
}

Vec3& Vec3::operator/=(const float t) {
  if (t == 0) {
    throw ZeroDivision();
  }
  x /= t;
  y /= t;
  z /= t;
  return *this; 
}

Vec3 Vec3::operator-() const {
  return Vec3(-x, -y, -z);
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs.getX() - rhs.getX(),
              lhs.getY() - rhs.getY(),
              lhs.getZ() - rhs.getZ());
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs.getX() + rhs.getX(),
              lhs.getY() + rhs.getY(),
              lhs.getZ() + rhs.getZ());
}

Vec3 operator*(const float t, const Vec3& v) {
  return Vec3(v.getX() * t, v.getY() * t, v.getZ() * t);
}

Vec3 operator*(const Vec3& v, const float t) {
  return t * v; 
}

Vec3 Vec3::operator/(const float t) const {
  if (t == 0) {
    throw ZeroDivision();
  }
  return Vec3(x / t, y / t, z / t);
}

std::ostream& operator<<(std::ostream& o, const Vec3& v) {
  o << v.getX() << ' ' << v.getY() << ' ' << v.getZ();
  return o;
}

float Vec3::getX() const {
  return x;
}

float Vec3::getY() const {
  return y;
}

float Vec3::getZ() const {
  return z;
}

float Vec3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

float Vec3::length_squared() const {
  return x * x + y * y + z * z;
}

Vec3 Vec3::unit() const {
  return *this / length();
}

Vec3 Vec3::toPixelColor() const {
  return Vec3(static_cast<int>(x * 255),
              static_cast<int>(y * 255),
              static_cast<int>(z * 255));
}

float dot(const Vec3& lhs, const Vec3& rhs) {
  return lhs.getX() * rhs.getX() +
         lhs.getY() * rhs.getY() +
         lhs.getZ() * rhs.getZ();

}

const char* Vec3::ZeroDivision::what() const throw() {
  return "Zero division";
}

