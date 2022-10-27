#include <iostream>
#include <fstream>
#include <cmath>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

// Image
const float kAspectRation = 16 / 9;
const int   kImageWidth = 1024;
const int   kImageHeight = static_cast<int>(kImageWidth / kAspectRation);

// Camera
const float  kViewPortHeight = 2.0f;
const float  kViewPortWidth = kViewPortHeight * kAspectRation;
const float  kFocalLength = 1.0f;

const Point3 kViewPoint = Point3(0, 0, 0);
const Vec3   kHorizontal = Vec3(kViewPortWidth, 0, 0);
const Vec3   kVertical = Vec3(0, kViewPortHeight, 0);
const Point3 kLowerLeftCorner =
  kViewPoint - kHorizontal / 2 - kVertical / 2 - Vec3(0, 0, kFocalLength); 

void printProgressInfo(int lineNb) {
  std::cerr << "\rScanlines remaining: " << lineNb << " " << std::flush;
}

void flushProgressInfo() {
  std::cerr << '\r' << std::string(100, ' ') << '\r';
}

Color getRayColor(const Ray& ray) {
  auto sphere = Sphere(Point3(0, 0, -1), 0.5);
  auto hitRecord = HitRecord();

  if (sphere.hit(ray, 0, 100, hitRecord)) {
    Vec3 norm = hitRecord.norm;
    return 0.5f * Color(norm.getX() + 1, norm.getY() + 1, norm.getZ() + 1);
  }
  
  Vec3 unitVec = ray.getDirection().unit();
  float t = (unitVec.getY() + 1) * 0.5;
  return Color(1, 1, 1) * (1 - t) + Color(0.5, 0.7, 1) * t;
}

void renderTo(std::ofstream& file) {
  // Header
  file << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

  // Image
  for (int i = kImageHeight - 1; i >= 0; --i) {
    printProgressInfo(i);
    for (int j = 0; j < kImageWidth; ++j) {
      float U = static_cast<float>(j) / (kImageWidth - 1);
      float V = static_cast<float>(i) / (kImageHeight - 1);
      Vec3 direction =
        kLowerLeftCorner + kHorizontal * U + kVertical * V - kViewPoint;
      Ray ray = Ray(kViewPoint, direction);
      file << getRayColor(ray).toPixelColor() << "\n";
    } 
  }

  flushProgressInfo();
}

int main() {
  std::ofstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    file.open("img.ppm");
    renderTo(file);
  } catch (std::ifstream::failure& e) {
    std::cerr << "Exception opening/reading/closing file\n";
  }

  return 0;
}
