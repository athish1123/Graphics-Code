#include "lambertian_shader.h"

Color LambertianShader::render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const
{
    // Render magenta if given bad data.
    if (normal.length() < 1e-12) {
        return Shader::render(point, normal, lights);
    }

    Color sum(0.0, 0.0, 0.0);

    for (const std::shared_ptr<Light>& light : lights) {
        if (!light) {
            continue;
        }

        // Vector from the surface point to the light.
        Vec3 dist_to_light = light->position - point;
        if (dist_to_light.length() < 1e-12) {
            continue;
        }

        // Clamp so back faces receive no diffuse light.
        double dot_prod = std::max(0.0, dot(normalize(normal), normalize(dist_to_light)));
        sum += light->color * (light->intensity * dot_prod);
    }

    return Color::fromVec3(albedo * sum);
}
