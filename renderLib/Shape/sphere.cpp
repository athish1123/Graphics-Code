#include "sphere.h"

bool Sphere::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec)
{
    Vec3 rayOriginToCenter = center - ray.getOrigin();
    auto rayDirSquared = dot(ray.getDirection(), ray.getDirection());
    auto rayDirDotCenterOffset = -2.0 * dot(ray.getDirection(), rayOriginToCenter);
    auto centerOffsetSquared  = dot(rayOriginToCenter,rayOriginToCenter) - (radius * radius); 
    auto discriminant = rayDirDotCenterOffset * rayDirDotCenterOffset - 4 * rayDirSquared * centerOffsetSquared ;
    return discriminant > 0;
}