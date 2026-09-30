#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "vec3.h"

struct PointLight
{
    Vec3 position;
    Color internsity = Color(1.0, 1.0, 1.0);
};

#endif