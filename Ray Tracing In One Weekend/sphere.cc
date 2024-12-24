#include "sphere.h"


sphere::sphere(const point3& c, double r, shared_ptr<material> mat): center{c}, radius{std::fmax(0, r)}, mat{mat} {}

bool sphere::hit(const ray& r, interval bounds, hit_record& rec) const {
  vec3 oc = center - r.origin();
  double a = r.direction().norm_squared();
  double h = dot(r.direction(), oc);
  double c = oc.norm_squared() - radius*radius;

  double d = h*h - a*c;
  if (d < 0)
    return false;

  double sqrtd = std::sqrt(d);
  // Find the nearest sqaure that falls in the acceptable range
  double root = (h - sqrtd) / a;
  if (!bounds.surrounds(root)) {
    root = (h + sqrtd) / a;
    if (!bounds.surrounds(root))
      return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat = mat;

  return true;
}