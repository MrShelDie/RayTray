#include "Camera.hpp"

Camera::Camera() :
    viewPoint(Point3(0, 0, 0)),
    horizontal(Vec3(kViewPortWidth, 0.0, 0.0)),
    vertical(Vec3(0.0, kViewPortHeight, 0.0)),
    lowerLeftCorner(viewPoint - horizontal/2 - vertical/2 - Vec3(0, 0, kFocalLength)) {

}

Camera::Camera(const Camera& c) : Camera() {

}

Camera::~Camera() {

}

Camera& Camera::operator=(const Camera& c) {
  return *this;
}

Ray Camera::getRay(float u, float v) const {
  return Ray(viewPoint, lowerLeftCorner + u*horizontal + v*vertical - viewPoint);
}

const float Camera::kAspectRation = 16 / 9;
const float Camera::kViewPortHeight = 2.0f;
const float Camera::kViewPortWidth = kViewPortHeight * kAspectRation;
const float Camera::kFocalLength = 1.0f;

const int Camera::kImageWidth = 1024;
const int Camera::kImageHeight = static_cast<int>(kImageWidth / kAspectRation);
