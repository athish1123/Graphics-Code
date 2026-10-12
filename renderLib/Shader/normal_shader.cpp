#include "normal_shader.h"

#include <cmath>

Color NormalShader::render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const
{
    double length = std::sqrt(
        normal.x() * normal.x() +
        normal.y() * normal.y() +
        normal.z() * normal.z()
    );
    double inv_length = 1.0 / length;

    return Color(
        0.5 * (normal.x() * inv_length + 1.0),
        0.5 * (normal.y() * inv_length + 1.0),
        0.5 * (normal.z() * inv_length + 1.0)
    );
}
