#include "mirror_shader.h"

Color MirrorShader::render(const Vec3 &point, const Vec3 &normal, const std::vector<const Light *> &lights) const
{
    if (normal.length() < 1e-12) {
        return Shader::render(point, normal, lights);
    }

    Vec3 N = normalize(normal);

    Color sum(0.0, 0.0, 0.0);

    for(const Light* light : lights)
    {
        if (!light) 
        {
            continue;
        }

        // Vector from the surface point to the light.
        Vec3 dist_to_light = light->position - point;
        if (dist_to_light.length() < 1e-12) 
        {
            continue;
        }
    
        Vec3 L = normalize(dist_to_light);
        double diffuse = std::max(0.0, dot(N, L));

        sum += light->color * (light->intensity*diffuse);
    }
    
    return Color::fromVec3(tint * sum);
}