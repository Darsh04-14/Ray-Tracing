#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  private:
  
  point3 orig;
  vec3 dir;

  public:

  ray();
  ray(const point3&, const vec3&);

  const point3& origin() const;
  const vec3& direction() const;

  point3 at(double) const;

};

#endif