#include "metal.h"


metal::metal(const color& c, double fuzz): albedo{c}, fuzz{fuzz < 1 ? fuzz : 1} {}

bool metal::scatter(const ray& ray_in, const hit_record& rec, color& attentuation, ray& scattered) const {
  vec3 reflected = reflect(ray_in.direction(), rec.normal);
  reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
  scattered = ray{rec.p, reflected};
  attentuation = albedo;

  return dot(scattered.direction(), rec.normal) > 0;
}