#include "shape.h"

#include <utility>

Shape::Shape(std::shared_ptr<Shader> shader_ptr)
    : shader(shader_ptr ? std::move(shader_ptr) : std::make_shared<Shader>())
{
}
