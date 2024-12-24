#include "hittable_list.h"

hittable_list::hittable_list(shared_ptr<hittable> object) { add(object); }

void hittable_list::clear() { objects.clear(); }
void hittable_list::add(shared_ptr<hittable> object) { objects.push_back(object); }

bool hittable_list::hit(const ray&r, interval bounds, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_hit = bounds.max;

  for (const auto& obj : objects) {
    if (obj->hit(r, interval{bounds.min, closest_hit}, temp_rec)) {
      hit_anything = true;
      closest_hit = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}