#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <exception>

class Vec3 {
 public:

  static Vec3 randVec();
  static Vec3 randVec(float min, float max);
  static Vec3 randVecInUnitSphere();
  static Vec3 randUnitVec();

  class ZeroDivision : std::exception {
    public:
     const char* what() const throw();
  };

  Vec3();
  Vec3(const Vec3& v);
  Vec3(float x, float y, float z);
  ~Vec3();

  Vec3& operator=(const Vec3& v);  
  Vec3& operator+=(const Vec3& v);
  Vec3& operator*=(const float t);
  Vec3& operator/=(const float t);

  Vec3  operator-() const;
  Vec3  operator/(const float t) const;  

  float getX() const;
  float getY() const;
  float getZ() const;

  float length() const;
  float lengthSquared() const;
  Vec3  unit() const;
  Vec3  toPixelColor(int samplesPerPixel) const;

 private:
  float x;
  float y;
  float z;
};

std::ostream& operator<<(std::ostream& o, const Vec3& v);

Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
Vec3 operator*(const float t, const Vec3& v);
Vec3 operator*(const Vec3& v, const float t);

float dot(const Vec3& lhs, const Vec3& rhs);

using Color = Vec3;
using Point3 = Vec3;

#endif
