#include "HittableList.hpp"

HittableList::HittableList() {

}

HittableList::HittableList(const HittableList& other) : objs(other.size()) {
  copyVector(other.objs);
}

HittableList::~HittableList() {

} 

HittableList& HittableList::operator=(const HittableList& other) {
  if (&other != this) {
    copyVector(other.objs);
  }
  return *this;
}

void HittableList::copyVector(vector<shared_ptr<IHittable>> otherObjs) {
  if (objs.size() != otherObjs.size()) {
    objs.resize(otherObjs.size());
  }

  for (size_t i = 0; i < otherObjs.size(); ++i) {
    if (otherObjs[i]) {
      // objs[i] = make_shared<IHittable>(otherObjs[i]->copy());
      objs[i] = shared_ptr<IHittable>(otherObjs[i]->copy());
    }
  }
}

size_t HittableList::size() const {
  return objs.size();
}

void HittableList::clear() {
  objs.clear();
}

void HittableList::append(const shared_ptr<IHittable>& obj) {
  objs.push_back(obj); 
}

IHittable* HittableList::copy() const {
  return new HittableList; 
}

bool HittableList::hit(const Ray& ray, float tMin, float tMax,
                         HitRecord& hitRec) const {
  HitRecord tempRec;
  bool hitAnythig = false;
  float closestSoFar = tMax;

  for (const auto& obj : objs) {
    if (obj->hit(ray, tMin, closestSoFar, tempRec)) {
      hitAnythig = true;
      closestSoFar = tempRec.t;
      hitRec = tempRec;
    }
  }

  return hitAnythig;
}
