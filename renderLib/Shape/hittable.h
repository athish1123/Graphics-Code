#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

struct HitRecord{
    Point3 rayHitPoint;       //The point in space where the ray hit
    Vec3 surfaceNormal;    //The surface normal at that point
    double rayHitParameter;       //The ray parameter at which the hit occured

    bool front_face;
    void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = dot(ray.getDirection(), outward_normal) < 0;
        surfaceNormal = front_face ? outward_normal : -outward_normal;
    }

};

// Abstract base class
class Hittable{
    public:
        // returns true if r hits this sahpe for some t in (t_min t_max)
        // On a hit fills in rec with the closest such intersect
        virtual bool intersect(const Ray& ray, double t_min, double t_max, HitRecord& hit) const = 0;

};

#endif