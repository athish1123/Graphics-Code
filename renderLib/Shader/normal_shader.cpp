#include "normal_shader.h"

Color NormalShader::render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const
{
    const Vec3 unitNormal = normalize(normal);

    return Color(
        0.5 * (unitNormal.x() + 1.0),
        0.5 * (unitNormal.y() + 1.0),
        0.5 * (unitNormal.z() + 1.0)
    );
}
