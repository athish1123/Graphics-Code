#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <memory>

#include "../Shader/shader.h"
#include "../Shape/shape.h"
#include "vec3.h"

class Triangle : public Shape {
	public:
		Triangle(const Vec3& point0, const Vec3& point1, const Vec3& point2);
		Triangle(const Vec3& point0, const Vec3& point1, const Vec3& point2, std::shared_ptr<Shader> shader);

		bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

	private:
		Vec3 point0;
		Vec3 point1;
		Vec3 point2;
};

#endif

// im a fat chubby seal yummy yummy yummy 