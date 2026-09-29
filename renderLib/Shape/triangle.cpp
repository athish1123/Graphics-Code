#include "triangle.h"


bool Triangle::intersect(const Ray& ray, double t_min, double t_max, HitRecord& hit) const
{
    const double EPS = 1e-8;

    Vec3 e1 = b - a;
    Vec3 e2 = c - a;
    Vec3 p = cross(ray.getDirection(), e2);
    double det = dot(e1, p);
    if (std::fabs(det) < EPS) return false;      // ray parallel to triangle

    double invDet = 1.0 / det;
    Vec3 s = ray.getOrigin() - a;
    double u = dot(s, p) * invDet;
    if (u < 0.0 || u > 1.0) return false;

    Vec3 q = cross(s, e1);
    double v = dot(ray.getDirection(), q) * invDet;
    if (v < 0.0 || u + v > 1.0) return false;

    double t = dot(e2, q) * invDet;
    if (t < t_min || t > t_max) return false;

    hit.rayHitParameter  = t;
    hit.rayHitPoint  = ray.getOrigin() + t * ray.getDirection();
    hit.set_face_normal(ray, normalize(cross(e1, e2)));
    return true;
}

