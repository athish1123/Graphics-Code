#include "sphere.h"

using namespace std;

bool Sphere::intersect(const Ray& ray, double t_min, double t_max, HitRecord& hit) const
{
    Vec3 rayOriginToCenter = center - ray.getOrigin();
    
    auto rayDirSquared = ray.getDirection().length_squared();
    auto rayDirDotCenter = dot(ray.getDirection(), rayOriginToCenter);
    auto centerOffsetSquared  = rayOriginToCenter.length_squared() - (radius * radius); 
   
    auto discriminant = rayDirDotCenter * rayDirDotCenter - rayDirSquared * centerOffsetSquared ;
    
    if (discriminant < 0)
    {
        return false;
    }

    auto sqrtDiscriminant = sqrt(discriminant);

    auto root = (rayDirDotCenter - sqrtDiscriminant) / rayDirSquared;
    if(root <= t_min || root >= t_max)
    {
        root = (rayDirDotCenter + sqrtDiscriminant) / rayDirSquared;
        if(root <= t_min || root >= t_max)
        {
            return false;
        }
    }

    hit.rayHitParameter = root;
    hit.rayHitPoint = ray.rayAt(hit.rayHitParameter);
    Vec3 outward_normal = (hit.rayHitPoint - center) / radius;
    hit.set_face_normal(ray, outward_normal);

    return true;
}



