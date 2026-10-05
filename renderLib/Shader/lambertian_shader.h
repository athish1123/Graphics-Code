#ifndef LAMBERTIAN_SHADER_H
#define LAMBERTIAN_SHADER_H

#include "shader.h"
#include <algorithm>
#include <cmath>

using namespace std;

class LambertianShader : public Shader
{
public:
	explicit LambertianShader(const Color& albedo) : albedo(albedo) {}

	Color shade(const HitRecord& hit, const PointLight& light) const override
	{
		Vec3 lightDirection = light.position - hit.rayHitPoint;
		const double distanceSquared = lightDirection.length_squared();
		if (distanceSquared == 0.0)
			return Color(0.0, 0.0, 0.0);

		lightDirection /= sqrt(distanceSquared);
		const double diffuse = max(0.0, dot(hit.surfaceNormal, lightDirection));
		return albedo * light.internsity * diffuse;
	}

private:
	Color albedo;
};

#endif