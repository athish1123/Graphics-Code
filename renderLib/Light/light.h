#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "vec3.h"

class Light {
	public:
		Light(
			const Vec3& position,
			const Color& color = Color(1.0, 1.0, 1.0),
			double intensity = 1.0
		) : position(position), color(color), intensity(intensity) {}

		Vec3 position;
		Color color;
		double intensity;
};

#endif