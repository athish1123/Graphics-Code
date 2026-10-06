#ifndef NORMAL_SHADER_H
#define NORMAL_SHADER_H

#include "shader.h"
#include "color.h"
#include "vec3.h"

#include <cmath>
#include <memory>

class NormalShader : public Shader {
	public:
		NormalShader() : Shader() {}

		Color render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const override {
			double length = std::sqrt(
				normal.x() * normal.x() +
				normal.y() * normal.y() +
				normal.z() * normal.z()
			);

			// // render magenta if given bad data
			// if (length < 1e-12) {
			// 	return Shader::render(point, normal);
                
			// }

			double inv_length = 1.0 / length;

			// remapping :)
			return Color(
				0.5 * (normal.x() * inv_length + 1.0),
				0.5 * (normal.y() * inv_length + 1.0),
				0.5 * (normal.z() * inv_length + 1.0)
			);
		}
};

#endif