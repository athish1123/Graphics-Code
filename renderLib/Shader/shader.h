#ifndef SHADER_H
#define SHADER_H

#include "color.h"
#include "vec3.h"
#include "../Light/light.h"

#include <vector>
#include <memory>

class Shader {
	public:
		Shader() : default_color(Color::magenta()) {}
		Shader(const Color& color) : default_color(color) {}
		virtual ~Shader() = default;

		virtual Color render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const {
			return default_color;
		}

	private:
		Color default_color;
};

#endif