#include "lambertian.h"

lambertian::lambertian(const color& c): albedo{c} {}

bool lambertian::scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  vec3 scattered_direction = rec.normal + random_unit_vector();

  if (scattered_direction.near_zero())
    scattered_direction = rec.normal;
    
  scattered = ray(rec.p, scattered_direction);
  attenuation = albedo;
  return true;
}