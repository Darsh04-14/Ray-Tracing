#include "material.h"

class lambertian : public material {
  private:
  color albedo;

  public:

  lambertian(const color&);

  bool scatter(const ray&, const hit_record&, color&, ray&) const override;

};