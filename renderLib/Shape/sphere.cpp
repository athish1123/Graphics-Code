#include "../Shape/sphere.h"
#include "../Shader/shader.h"
#include "Ray.h"

#include <cmath>
#include <memory>
#include <utility>

Sphere::Sphere(const Vec3& center, double radius) :
	Shape(),
	center(center),
	radius(radius) {}

Sphere::Sphere(const Vec3& center, double radius, std::shared_ptr<Shader> shader) :
	Shape(std::move(shader)),
	center(center),
	radius(radius) {}
    
bool Sphere::intersect(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    Vec3 origin_to_center = center - ray.getOrigin();
    double a = ray.getDirection().length_squared();
    double h = dot(ray.getDirection(), origin_to_center);
    double c = origin_to_center.length_squared() - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    double sqrtd = std::sqrt(discriminant);

    double root = (h - sqrtd) / a;
    if (root <= t_min || root >= t_max) {
        root = (h + sqrtd) / a;
        if (root <= t_min || t_max <= root)
            return false;
    }

    // only update record if there's a good hit
    rec.t = root;
    rec.point = ray.rayAt(rec.t);
    rec.normal = (rec.point - center) / radius;
    rec.shader = shader;

    return true;
}