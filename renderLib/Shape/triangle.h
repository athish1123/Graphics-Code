#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "hittable.h"

class Triangle : public Hittable{
    public:

        Triangle(const Point3& v0, const Point3& v1, const Point3& v2) : a(v0), b(v1), c(v2) {}

        bool intersect(const Ray& r, double t_min, double t_max, HitRecord& hit) const override;

    private:
        Point3 a, b, c;
};

#endif