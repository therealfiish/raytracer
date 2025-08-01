//
// Created by Krrish ignore Kumar on 7/26/25.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
#include "hittable.h"
#include "ray.h"

class material {
    public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertian : public material {
    public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
    private:
    color albedo;
};
class metal : public material {
public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz*random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    private:
    color albedo;
    double fuzz;
};
class dielectric : public material {
    public:
    dielectric(double refract_i): refract_i(refract_i) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/refract_i) : refract_i;

        vec3 unit_dir = unit_vector(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;
        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_dir, rec.normal);
        else direction = refract(unit_dir, rec.normal, ri);
        scattered = ray(rec.p, direction);
        return true;
    }
    private:
    double refract_i;

    static double reflectance(double cosine, double refract_i) {
        auto r0 = (1 - refract_i) / (1 + refract_i);
        r0 = r0 * r0;
        return r0 + (1-r0)*pow((1 - cosine), 5);
    }
};
#endif //MATERIAL_H
