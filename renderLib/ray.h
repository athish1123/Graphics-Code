#ifndef RAY_H

#define RAY_H

#include "vec3.h"

class Ray{
    public:
    Ray() {}

    Ray(const Point3& origin, const Vec3& direction) : rayOrigin(origin), rayDirection(direction) {}

    const Point3& getOrigin() const { return rayOrigin; }
    const Vec3& getDirection() const { return rayDirection; }

    Point3 rayAt(double t) const { return rayOrigin + t * rayDirection; }

    private:
        Point3 rayOrigin;
        Vec3 rayDirection;
};

#endif 