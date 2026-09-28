#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"
#include "shape.h"

class Sphere : public Shape{
    public:
        Sphere(const Point3& center, double radius) : center(center), radius(radius){}

        bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) override{};

    private:
        Point3 center;
        double radius;    
};

#endif 