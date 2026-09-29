#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"

class Sphere : public Hittable{
    public:
        Sphere(const Point3& center, double radius) : center(center), radius(radius){}

        bool intersect(const Ray& r, double t_min, double t_max, HitRecord& hit) const override; // TA Showed this with override{} at the end

    private:
        Point3 center;
        double radius;    
};

#endif 