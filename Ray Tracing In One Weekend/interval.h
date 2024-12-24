#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

class interval {
  public:
  double min, max;
  
  interval();
  interval(double, double);

  double size() const;
  double clamp(double) const;

  bool contains(double) const;
  bool surrounds(double) const;


  static const interval empty, universe;
};

#endif