#include "shader.h"

Color Shader::render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const
{
    return default_color;
}
