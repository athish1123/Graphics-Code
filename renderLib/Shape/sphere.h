#ifndef SPHERE_H
#define SPHERE_H

#include "../Shader/shader.h"
#include "../Shape/shape.h"
#include "vec3.h"
#include "ray.h"

class Sphere : public Shape {
public:
    Sphere(const Vec3& center, double radius);
    Sphere(const Vec3& center, double radius, std::shared_ptr<Shader> shader);

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

private:
    Vec3 center;
    double radius;
};

#endif