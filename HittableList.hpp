#ifndef HITTABLE_VECTOR_H
#define HITTABLE_VECTOR_H

#include <vector>
#include <memory>

#include "IHittable.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;

class HittableList : public IHittable {
 public:
  HittableList();
  HittableList(const HittableList& other);
  virtual ~HittableList();

  HittableList& operator=(const HittableList& other);

  size_t size() const;

  void clear();
  void append(const shared_ptr<IHittable>& obj);


  virtual IHittable* copy() const override;
  virtual bool hit(
      const Ray& ray, float tMin, float tMax, HitRecord& hitRec) const override;

 private:
  void copyVector(vector<shared_ptr<IHittable>> other);

  vector<shared_ptr<IHittable>> objs;
};

#endif
