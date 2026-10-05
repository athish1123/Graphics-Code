#ifndef SHADER
#define SHADER


#include "../Light/point_light.h"
#include "../Shape/hittable.h"

class Shader
{
    public:
        virtual ~Shader() = default;
        virtual Color shade(const HitRecord& hit, const PointLight& light) const = 0;

};

#endif