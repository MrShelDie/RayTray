#include <iostream>
#include <fstream>

#include "RayTray.hpp"
#include "Camera.hpp"

// Hittable object
#include "HittableList.hpp"
#include "Sphere.hpp"

// material
#include "Metal.hpp"
#include "Lambertian.hpp"

void printProgressInfo(int lineNb) {
  std::cerr << "\rScanlines remaining: " << lineNb << " " << std::flush;
}

void flushProgressInfo() {
  std::cerr << '\r' << std::string(100, ' ') << '\r';
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
        accumulatedColor += ray.getColor(world, Camera::kMaxDepth);
      }
      file << accumulatedColor.toPixelColor(kSamplesPerPixel) << "\n";
    } 
  }

  flushProgressInfo();
}

void initWorld(HittableList& world) {
  auto materialGround = make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
  auto materialCenter = make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));
  auto materialLeft   = make_shared<Metal>(Color(0.8f, 0.8f, 0.8f));
  auto materialRight  = make_shared<Metal>(Color(0.8f, 0.6f, 0.2f));

  world.append(make_shared<Sphere>(
    Point3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
  world.append(make_shared<Sphere>(
    Point3(0.0f,    0.0f, -1.0f),   0.5f, materialCenter));
  world.append(make_shared<Sphere>(
    Point3(-1.0f,   0.0f, -1.0f),   0.5f, materialLeft));
  world.append(make_shared<Sphere>(
    Point3(1.0f,    0.0f, -1.0f),   0.5f, materialRight));
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
