//
// Created by Krrish Kishore Kumar on 7/26/25.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "hittable.h"
#include "ray.h"

class material {
    public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};
#endif //MATERIAL_H
