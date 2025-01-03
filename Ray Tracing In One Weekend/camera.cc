#include "camera.h"


void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  center = lookfrom;

  auto theta = degrees_to_radians(vfov);
  auto h = std::tan(theta/2);
  auto viewport_height = 2 * h * focus_dist;
  auto viewport_width = viewport_height * (double(image_width)/image_height);

  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
  vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
  defocus_disk_u = u * defocus_radius;
  defocus_disk_v = v * defocus_radius;
}

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
  if (depth <= 0) return color(0,0,0);
  hit_record rec;

  if (world.hit(r, interval(0.001, infinity), rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, depth - 1, world);
    } 
    return color{0,0,0};
  }

  vec3 unit_direction = unit_vector(r.direction());

  double a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {

  vec3 offset = sample_square();
  point3 pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

  point3 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
  vec3 ray_direction = pixel_sample - ray_origin;

  return ray{ray_origin, ray_direction};
}
vec3 camera::sample_square() const {
  return vec3{random_double() - 0.5, random_double() - 0.5, 0};
}

point3 camera::defocus_disk_sample() const {
  vec3 p = random_in_unit_disk();
  return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

void camera::render(const hittable& world) {
  initialize();
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  std::vector<std::thread> threads(image_height);
  std::vector<std::vector<color>> pixel_values(image_height, std::vector<color>(image_width));
  auto t1 = std::chrono::high_resolution_clock::now();

  auto get_scanline = [&](int j) {
    for (int i = 0; i < image_width; i++) {
      color pixel_color(0,0,0);
      for (int sample = 0; sample < samples_per_pixel; ++sample) {
        ray r = get_ray(i, j);
        pixel_color += ray_color(r, max_depth, world);
      }
      pixel_values[j][i] = pixel_samples_scale * pixel_color;
    }
  };

  for (int j = 0; j < image_height; ++j) threads[j] = std::thread(get_scanline, j);

  for (int j = 0; j < image_height; ++j) {
    if (threads[j].joinable())
      threads[j].join();
  }
  auto t2 = std::chrono::high_resolution_clock::now();

  for (const auto &i : pixel_values) {
    for (const auto &j : i)
      write_color(std::cout, j);
  }

  std::chrono::duration<double, std::milli> ms_double = (t2 - t1);
  std::clog << "\rDone. Time Elapsed: " << ms_double.count() / 1000 << "s                   \n";
}