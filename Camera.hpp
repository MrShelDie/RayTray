#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.hpp"

class Camera {
 public:
  static const int kImageWidth;
  static const int kImageHeight;
  static const int kMaxDepth;

  Camera();
  Camera(const Camera& c);
  ~Camera();

  Camera& operator=(const Camera& c);

  Ray getRay(float u, float v) const;

 private:
  static const float kAspectRation;
  static const float kViewPortHeight;
  static const float kViewPortWidth;
  static const float kFocalLength;

  Point3 viewPoint;
  Vec3   horizontal;
  Vec3   vertical;
  Point3 lowerLeftCorner;
};

#endif
