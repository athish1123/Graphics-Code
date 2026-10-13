#include "blinnphong_shader.h"

BlinnPhongShader::BlinnPhongShader(const Color& albedo, const Vec3& camera_pos, const Color& spec_color, double shininess, const Color& ambient)
    : Shader(), albedo(albedo), camera_pos(camera_pos), spec_color(spec_color), ambient(ambient), shininess(shininess)
{
}

Color BlinnPhongShader::render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const
{
    const double normalLengthSquared = normal.length_squared();
    if (normalLengthSquared < 1e-24) {
        return Shader::render(point, normal, lights);
    }

    const Vec3 N = normal / std::sqrt(normalLengthSquared);
    const Vec3 viewDirection = camera_pos - point;
    const double viewLengthSquared = viewDirection.length_squared();
    const Vec3 V = viewLengthSquared > 1e-24
        ? viewDirection / std::sqrt(viewLengthSquared)
        : Vec3();
    Vec3 sum = ambient * albedo;

    for (const Light* light : lights) {
        if (!light) {
            continue;
        }

        Vec3 to_light = light->position - point;
        const double lightLengthSquared = to_light.length_squared();
        if (lightLengthSquared < 1e-24) {
            continue;
        }

        const Vec3 L = to_light / std::sqrt(lightLengthSquared);
        double diff = std::max(0.0, dot(N, L));
        double spec = 0.0;
        if (diff > 0.0) {
            const Vec3 halfDirection = L + V;
            const double halfLengthSquared = halfDirection.length_squared();
            if (halfLengthSquared > 1e-24) {
                const double nDotH = std::max(0.0, dot(N, halfDirection / std::sqrt(halfLengthSquared)));
                spec = std::pow(nDotH, shininess);
            }
        }
        Vec3 light_col = light->color * light->intensity;
        sum += light_col * albedo * diff;
        sum += light_col * spec_color * spec;
    }

    return Color::fromVec3(sum);
}
