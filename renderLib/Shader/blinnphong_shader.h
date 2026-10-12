#ifndef BLINNPHONG_SHADER_H
#define BLINNPHONG_SHADER_H

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "shader.h"
#include "Light/light.h"
#include "color.h"
#include "vec3.h"

class BlinnPhongShader : public Shader {
	public:
		BlinnPhongShader(const Color& albedo, const Vec3& camera_pos, const Color& spec_color = Color::white(), double shininess = 32.0, const Color& ambient = Color(0.1, 0.1, 0.1));

		Color render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const override;

	private:
		Color albedo;
		Vec3 camera_pos;
		Color spec_color;
		Color ambient;
		double shininess;
};

#endif