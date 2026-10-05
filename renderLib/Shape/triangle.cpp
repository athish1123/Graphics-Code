#include "triangle.h"
#include "color.h"

#include <cmath>
#include <memory>
#include <utility>
Triangle::Triangle(const Vec3& point0, const Vec3& point1, const Vec3& point2) :
	Shape(),
	point0(point0),
	point1(point1),
	point2(point2) {}

Triangle::Triangle(const Vec3& point0, const Vec3& point1, const Vec3& point2, std::shared_ptr<Shader> shader) :
	Shape(std::move(shader)),
	point0(point0),
	point1(point1),
	point2(point2) {}

bool Triangle::intersect(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    const double epsilon = 1e-8;

    Vec3 edge1 = point1 - point0;
    Vec3 edge2 = point2 - point0;

    Vec3 pvec = cross(ray.getDirection(), edge2);
    double determinant = dot(edge1, pvec);

    if (std::fabs(determinant) < epsilon)
        return false;

    double inverse_determinant = 1.0 / determinant;

    Vec3 tvec = ray.getOrigin() - point0;
    double u = dot(tvec, pvec) * inverse_determinant;
    if (u < 0.0 || u > 1.0)
        return false;

    Vec3 qvec = cross(tvec, edge1);
    double v = dot(ray.getDirection(), qvec) * inverse_determinant;
    if (v < 0.0 || u + v > 1.0)
        return false;

    double root = dot(edge2, qvec) * inverse_determinant;
    if (root <= t_min || root >= t_max)
        return false;

    rec.t = root;
    rec.point = ray.rayAt(rec.t);
    rec.normal = normalize(cross(edge1, edge2));
    rec.shader = shader;

    return true;
}