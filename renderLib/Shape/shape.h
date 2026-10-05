#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "ray.h"
#include "../Shape/hitrecord.h"
#include "../Shader/shader.h"

// Abstract base class
class Shape {
	public:
		Shape() : shader(std::make_shared<Shader>()) {}
		Shape(std::shared_ptr<Shader> shader_ptr)
			: shader(shader_ptr ? std::move(shader_ptr) : std::make_shared<Shader>()) {}

		virtual ~Shape() = default;

		virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;

		std::shared_ptr<Shader> shader;
};

#endif