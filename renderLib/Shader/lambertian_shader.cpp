#include "lambertian_shader.h"

#include <cmath>

Color LambertianShader::render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const
{
    const double normalLengthSquared = normal.length_squared();
    if (normalLengthSquared < 1e-24) {
        return Shader::render(point, normal, lights);
    }

    const Vec3 unitNormal = normal / std::sqrt(normalLengthSquared);
    Color sum(0.0, 0.0, 0.0);

    for (const Light* light : lights) {
        if (!light) {
            continue;
        }

        // Vector from the surface point to the light.
        Vec3 dist_to_light = light->position - point;
        const double lightDistanceSquared = dist_to_light.length_squared();
        if (lightDistanceSquared < 1e-24) {
            continue;
        }

        // Clamp so back faces receive no diffuse light.
        double dot_prod = std::max(
            0.0,
            dot(unitNormal, dist_to_light / std::sqrt(lightDistanceSquared))
        );
        sum += light->color * (light->intensity * dot_prod);
    }

    return Color::fromVec3(albedo * sum);
}
