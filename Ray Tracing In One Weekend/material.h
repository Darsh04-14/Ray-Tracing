#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"

class hit_record;

class material {
  public:

  virtual ~material() = default;

  virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    return false;
  }
};

#endif