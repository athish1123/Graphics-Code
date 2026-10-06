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

		Color render(const Vec3& point, const Vec3& normal, std::vector<std::shared_ptr<Light>> lights) const override {

			// render magenta if given bad data
			if (normal.length() < 1e-12) {
				return Shader::render(point, normal, lights);
			}

			Color sum(0.0, 0.0, 0.0);

			for (const std::shared_ptr<Light>& light : lights) {
				if (!light) {
					continue;
				}
				// vector from the surface point to the light
				Vec3 dist_to_light = light->position - point;
                // exclude super close lights
				if (dist_to_light.length() < 1e-12) {
					continue;
				}
				// clamped so back faces receive no diffuse light
				double dot_prod = std::max(0.0, dot(normalize(normal), normalize(dist_to_light)));

				sum += light->color * (light->intensity * dot_prod);
			}

			return Color::fromVec3(albedo * sum);
		}

	private:
		Color albedo;
};

#endif