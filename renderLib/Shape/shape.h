#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "ray.h"
#include "aabb.h"
#include "../Shape/hitrecord.h"
#include "../Shader/shader.h"

// Abstract base class
class Shape {
	public:
		Shape() : shader(std::make_shared<Shader>()) {}
		Shape(std::shared_ptr<Shader> shader_ptr);

		virtual ~Shape() = default;

		virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
		virtual bool bounding_box(Aabb& bounds) const { return false; }

		std::shared_ptr<Shader> shader;
};

#endif