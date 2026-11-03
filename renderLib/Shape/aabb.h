#ifndef AABB_H
#define AABB_H

#include "ray.h"
#include "vec3.h"

#include <algorithm>

class Aabb {
public:
    Aabb() = default;
    Aabb(const Vec3& minimum, const Vec3& maximum)
        : minimum(minimum), maximum(maximum) {}

    bool hit(const Ray& ray, double t_min, double t_max) const
    {
        for (int axis = 0; axis < 3; ++axis) {
            const double origin = ray.getOrigin()[axis];
            const double direction = ray.getDirection()[axis];

            if (direction == 0.0) {
                if (origin < minimum[axis] || origin > maximum[axis]) {
                    return false;
                }
                continue;
            }

            double t0 = (minimum[axis] - origin) / direction;
            double t1 = (maximum[axis] - origin) / direction;
            if (t0 > t1) {
                std::swap(t0, t1);
            }

            t_min = std::max(t_min, t0);
            t_max = std::min(t_max, t1);
            if (t_max < t_min) {
                return false;
            }
        }

        return true;
    }

    static Aabb surroundingBox(const Aabb& first, const Aabb& second)
    {
        return Aabb(
            Vec3(
                std::min(first.minimum.x(), second.minimum.x()),
                std::min(first.minimum.y(), second.minimum.y()),
                std::min(first.minimum.z(), second.minimum.z())),
            Vec3(
                std::max(first.maximum.x(), second.maximum.x()),
                std::max(first.maximum.y(), second.maximum.y()),
                std::max(first.maximum.z(), second.maximum.z())));
    }

    Vec3 centroid() const
    {
        return minimum + 0.5 * (maximum - minimum);
    }

    Vec3 extent() const
    {
        return maximum - minimum;
    }

    Vec3 minimum;
    Vec3 maximum;
};

#endif
