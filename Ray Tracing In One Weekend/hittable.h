#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"
#include "interval.h"

using std::make_shared;
using std::shared_ptr;

class material;

class hit_record {
  public:
  point3 p;
  vec3 normal;
  shared_ptr<material> mat;
  double t;
  bool front_face;

  void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
  public:
  virtual ~hittable() = default;

  virtual bool hit(const ray&, interval, hit_record&) const = 0;
};

#endif