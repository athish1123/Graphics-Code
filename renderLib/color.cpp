#include "color.h"

#include <algorithm>

void Color::write_color(std::ostream& out, const Color& pixel_color)
{
    const auto toByte = [](double component) {
        return static_cast<int>(255.999 * std::clamp(component, 0.0, 1.0));
    };
    out << toByte(pixel_color.x()) << ' '
        << toByte(pixel_color.y()) << ' '
        << toByte(pixel_color.z()) << '\n';
}

Color Color::fromVec3(Vec3 vec)
{
    return Color(vec.x(), vec.y(), vec.z());
}
