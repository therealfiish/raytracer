//
// Created by Krrish Kishore Kumar on 7/25/25.
//

#ifndef VEC3_H
#define VEC3_H

class vec3 {
public:
    double e[3];

    vec3() : e{0, 0, 0} {
    }

    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {
    }

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }
    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    bool near_zero() const {
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }
    static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline vec3 operator+(const vec3 &a, const vec3 &b) {
    return vec3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]);
}
inline vec3 operator-(const vec3 &a, const vec3 &b) {
    return vec3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]);
}
inline vec3 operator*(const vec3 &a, const vec3 &b) {
    return vec3(a.e[0] * b.e[0], a.e[1] * b.e[1], a.e[2] * b.e[2]);
}
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}
inline vec3 operator/(const vec3 &v, double t) {
    return (1/t)*v;
}
inline double dot(const vec3 &a, const vec3 &b) {
    return a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2];
}
inline vec3 cross(const vec3 &a, const vec3 &b) {
    return vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1], a.e[2] * b.e[0] - a.e[0] * b.e[2], a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}
inline vec3 unit_vector(const vec3 &v) {
    return v / v.length();
}
inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length() < 1) return p;
    }
}
inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}
inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0)
        return on_unit_sphere;
    return -on_unit_sphere;
}
inline vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n;
}
inline vec3 refract(const vec3 &v, const vec3 &n, double eta) {
    auto cos_theta = std::fmin(dot(-v, n), 1.0);
    vec3 r_out_perp = eta * (v + cos_theta * n);
    vec3 r_out_parallel = -sqrt(std::fabs(1.0-r_out_perp.length_squared()))*n;
    return r_out_perp + r_out_parallel;
}
#endif //VEC3_H
