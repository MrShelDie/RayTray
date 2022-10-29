#include <iostream>
#include <fstream>

#include "RayTray.hpp"
#include "Camera.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"

void printProgressInfo(int lineNb) {
  std::cerr << "\rScanlines remaining: " << lineNb << " " << std::flush;
}

void flushProgressInfo() {
  std::cerr << '\r' << std::string(100, ' ') << '\r';
}

Color getRayColor(const Ray& ray, const HittableList& world) {
  HitRecord hitRec;

  if (world.hit(ray, 0, kInfinity, hitRec)) {
    return 0.5f * (hitRec.norm + Color(1, 1, 1));
  }
  
  Vec3 unitDirection = ray.getDirection().unit();
  float t = 0.5f * (unitDirection.getY() + 1);
  return (1 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1);
}

void renderTo(std::ofstream& file, 
    const HittableList& world, const Camera& cam) {
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
      file << getRayColor(ray, world).toPixelColor() << "\n";
    } 
  }

  flushProgressInfo();
}

void initWorld(HittableList& world) {
  world.append(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.append(make_shared<Sphere>(Point3(0, -100.5, -1), 100)); 
}

int main() {
  HittableList world;
  initWorld(world);

  Camera cam;

  std::ofstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    file.open("img.ppm");
    renderTo(file, world, cam);
  } catch (std::ifstream::failure& e) {
    std::cerr << "Exception opening/reading/closing file\n";
  }

  return 0;
}
