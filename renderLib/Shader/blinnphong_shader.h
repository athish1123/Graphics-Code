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
		BlinnPhongShader(const Color& albedo, const Vec3& camera_pos, const Color& spec_color = Color::white(), double shininess = 32.0, const Color& ambient = Color(0.1, 0.1, 0.1))
			: Shader(), albedo(albedo), camera_pos(camera_pos), spec_color(spec_color), ambient(ambient), shininess(shininess) {}

		Color render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const override {

			if (normal.length() < 1e-12) {
				return Shader::render(point, normal, lights);
			}

			Vec3 N = normalize(normal);
			Vec3 V = normalize(camera_pos - point);

			Vec3 sum = ambient * albedo;

			for (const std::shared_ptr<Light>& light : lights) {
				if (!light) continue;

				Vec3 to_light = light->position - point;
				if (to_light.length() < 1e-12) continue;

				Vec3 L = normalize(to_light);
				Vec3 H = normalize(L + V);

				double diff = std::max(0.0, dot(N, L));
				double spec = diff > 0.0 ? std::pow(std::max(0.0, dot(N, H)), shininess) : 0.0;

				Vec3 light_col = light->color * light->intensity;
				sum += light_col * albedo * diff;
				sum += light_col * spec_color * spec;
			}

			return Color::fromVec3(sum);
		}

	private:
		Color albedo;
		Vec3 camera_pos;
		Color spec_color;
		Color ambient;
		double shininess;
};

#endif