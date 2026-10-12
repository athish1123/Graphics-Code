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

		Color render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const override;
};

#endif