#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"

class sphere : public hittable {
  private:
  point3 center;
  double radius;
  shared_ptr<material> mat;

  public:
  sphere(const point3&, double, shared_ptr<material>);

  bool hit(const ray&, interval, hit_record&) const override;
};

#endif