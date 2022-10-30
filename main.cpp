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

Color getRayColor(const Ray& ray, const HittableList& world, int depth) {
  if (depth <= 0) {
    return Color(0, 0, 0);
  }

  HitRecord hitRec;

  if (world.hit(ray, 0.001f, kInfinity, hitRec)) {
   // if (hitRec.norm.getY() < 0) {
   //   std::cout << ray.getOrigin() << " " << ray.getDirection() << " " << hitRec.t << "\n";
   //   // std::cout << depth << "\n";
   // }
    Point3 target = hitRec.p + hitRec.norm + Vec3::randInUnitSphere();
    return 0.2f * getRayColor(Ray(hitRec.p, target - hitRec.p), world, depth-1);
  }
  
  Vec3 unitDirection = ray.getDirection().unit();
  float t = 0.5f * (unitDirection.getY() + 1);
  return (1 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1);
}

void renderTo(std::ofstream& file, 
    const HittableList& world, const Camera& cam) {
  // Header
  file << "P3\n" << Camera::kImageWidth  << ' '
                 << Camera::kImageHeight << "\n255\n";

  // Image
  for (int i = Camera::kImageHeight - 1; i >= 0; --i) {
    printProgressInfo(i);
    for (int j = 0; j < Camera::kImageWidth; ++j) {
      Color accumulatedColor(0, 0, 0);
      for (int s = 0; s < kSamplesPerPixel; ++s) {
        float u = (j + randFloat()) / (Camera::kImageWidth - 1);
        float v = (i + randFloat()) / (Camera::kImageHeight - 1);
        Ray ray = cam.getRay(u, v);
        accumulatedColor += getRayColor(ray, world, Camera::kMaxDepth);
      }
      file << accumulatedColor.toPixelColor(kSamplesPerPixel) << "\n";
    } 
  }

  flushProgressInfo();
}

void initWorld(HittableList& world) {
  world.append(make_shared<Sphere>(Point3(-0.3, 0, -1.2), 0.5));
  world.append(make_shared<Sphere>(Point3(0.69, 0, -1), 0.5));
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
