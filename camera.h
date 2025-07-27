//
// Created by Krrish Kishore Kumar on 7/25/25.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "hittable.h"
#include "vec3.h"

class camera {
  public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    img_w  = 100;  // Rendered image width in pixel count
    int samples_per_pixel = 1000;
    int max_depth = 100;
    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

        for (int j = 0; j < img_h; j++) {
            std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
            for (int i = 0; i < img_w; i++) {
                color pixel_color = color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i,j);
                    pixel_color += ray_color(r,max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int    img_h;   // Rendered image height
    double pixel_samples_scale;
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() {
        img_h = int(img_w / aspect_ratio);
        img_h = (img_h < 1) ? 1 : img_h;

        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(img_w)/img_h);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / img_w;
        pixel_delta_v = viewport_v / img_h;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    ray get_ray(int x, int y) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + ((x + offset.x()) * pixel_delta_u) + ((y + offset.y()) * pixel_delta_v);
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }
    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    color ray_color(const ray& r, int depth, const hittable& world) const {
        if (depth <= 0) return color(0,0,0);
        hit_record rec;
        if (world.hit(r,interval(0.00001, infinity), rec)) {
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5*ray_color(ray(rec.p, direction), depth-1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};
#endif //CAMERA_H
