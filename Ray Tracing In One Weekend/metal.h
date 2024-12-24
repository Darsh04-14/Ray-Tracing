#include "material.h"

class metal : public material {
  private:
  color albedo;
  double fuzz;

  public:
  metal(const color&, double);
  bool scatter(const ray&, const hit_record&, color&, ray&) const override;
};