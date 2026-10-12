#include "shader.h"

Color Shader::render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const
{
    return default_color;
}
