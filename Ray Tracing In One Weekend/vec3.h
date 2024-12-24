#ifndef VEC3_H
#define VEC3_H

#include "rtweekend.h"
#include <cmath>
#include <iostream>

class vec3 {
  public:
  double e[3];

  vec3();
  vec3(double, double, double);

  double x() const;
  double y() const;
  double z() const;

  vec3 operator-() const;
  double operator[](int) const;
  double& operator[](int);

  vec3& operator+=(const vec3&);
  vec3& operator*=(double);
  vec3& operator/=(double);

  double norm() const;
  double norm_squared() const;

  static vec3 random();
  static vec3 random(double, double);

  bool near_zero() const;
};

using point3 = vec3;

// Vector Util Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 operator*(double t, const vec3& v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3 operator*(const vec3& v, double t) {
  return t * v;
}
inline vec3 operator/(const vec3& v, double t) {
  return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
inline vec3 cross(const vec3& u, const vec3& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline vec3 unit_vector(const vec3& v) {
  return v / v.norm();
}

inline vec3 random_unit_vector() {
  while (true) {
    vec3 p = vec3::random(-1, 1);
    double normsq = p.norm_squared();
    if (1e-160 < normsq && normsq <= 1)
      return p / sqrt(normsq);
  }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0)
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v, n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
  double cos_theta = std::fmin(dot(-uv, n), 1.0);
  vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
  vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.norm_squared())) * n;
  return r_out_perp + r_out_parallel;
}

inline vec3 random_in_unit_disk() {
  while (true) {
    vec3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.norm_squared() < 1) return p;
  }
}

#endif