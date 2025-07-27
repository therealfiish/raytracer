//
// Created by Krrish Kishore Kumar on 7/25/25.
//

#ifndef HITTABLE_H
#define HITTABLE_H

class material;

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    shared_ptr<material> mat;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif //HITTABLE_H
