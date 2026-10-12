#ifndef LAMBERTIAN_SHADER_H
#define LAMBERTIAN_SHADER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "shader.h"
#include "Light/light.h"
#include "color.h"
#include "vec3.h"

class LambertianShader : public Shader {
	public:
		LambertianShader(const Color& albedo) : Shader(), albedo(albedo) {}

		Color render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const override;

	private:
		Color albedo;
};

#endif