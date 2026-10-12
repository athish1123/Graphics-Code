#include "blinnphong_shader.h"

BlinnPhongShader::BlinnPhongShader(const Color& albedo, const Vec3& camera_pos, const Color& spec_color, double shininess, const Color& ambient)
    : Shader(), albedo(albedo), camera_pos(camera_pos), spec_color(spec_color), ambient(ambient), shininess(shininess)
{
}

Color BlinnPhongShader::render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const
{
    if (normal.length() < 1e-12) {
        return Shader::render(point, normal, lights);
    }

    Vec3 N = normalize(normal);
    Vec3 V = normalize(camera_pos - point);
    Vec3 sum = ambient * albedo;

    for (const Light* light : lights) {
        if (!light) {
            continue;
        }

        Vec3 to_light = light->position - point;
        if (to_light.length() < 1e-12) {
            continue;
        }

        Vec3 L = normalize(to_light);
        Vec3 H = normalize(L + V);
        double diff = std::max(0.0, dot(N, L));
        double spec = diff > 0.0 ? std::pow(std::max(0.0, dot(N, H)), shininess) : 0.0;
        Vec3 light_col = light->color * light->intensity;
        sum += light_col * albedo * diff;
        sum += light_col * spec_color * spec;
    }

    return Color::fromVec3(sum);
}
