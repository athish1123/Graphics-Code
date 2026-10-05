#include "Camera/perspective_camera.h"
#include "Shader/lambertian_shader.h"
#include "Shape/sphere.h"
#include "framebuffer.h"

#include <iostream>
#include <limits>

int main()
{
	constexpr int imageWidth = 320;
	constexpr int imageHeight = 320;

	Framebuffer framebuffer(imageWidth, imageHeight);
	PerspectiveCamera camera(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0), 1.3, 2.0, imageWidth, imageHeight);
	Sphere sphere(Point3(0.0, 0.0, -2.0), 0.75);
	LambertianShader shader(Color(0.8, 0.3, 0.2));
	PointLight light;
	light.position = Point3(-2.0, 2.0, 0.0);

	for (int y = 0; y < imageHeight; ++y)
	{
		for (int x = 0; x < imageWidth; ++x)
		{
			int rayX = x;
			int rayY = imageHeight - 1 - y;
			Ray ray;
			camera.generateRay(rayX, rayY, ray);

			Color pixelColor(0.02, 0.02, 0.02);
			HitRecord hit;
			if (sphere.intersect(ray, 0.001, std::numeric_limits<double>::infinity(), hit))
				pixelColor = shader.shade(hit, light);

			framebuffer.setPixelColor(x, y, pixelColor);
		}
	}

	const char* imageName = "LambertianSphere.png";
	framebuffer.exportAsPNG(imageName);
	std::cout << "Wrote " << imageName << '\n';
	return 0;
}
