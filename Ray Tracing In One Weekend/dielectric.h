#include "material.h"
#include <cmath>

class dielectric: public material {
  private:
  double refraction_index;

  static double reflectance(double, double);

  public: 
  dielectric(double);

  bool scatter(const ray&, const hit_record&, color&, ray&) const override;
};