#ifndef HITRECORD_H
#define HITRECORD_H

#include "Vec3.h"
#include "Shader/shader.h"

#include <limits>
#include <memory>

struct HitRecord {
	Vec3 point;
	Vec3 normal;
	double t = std::numeric_limits<double>::infinity();
	std::shared_ptr<Shader> shader;
};

#endif
