#include "Camera/perspective_camera.h"
#include "Shader/lambertian_shader.h"
#include "Shape/scene.h"
#include "Shape/sphere.h"
#include "Shape/triangle.h"

#include <iostream>
#include <memory>

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Framebuffer framebuffer(width, height);
    auto camera = std::make_shared<PerspectiveCamera>(
        Vec3(0.0, 0.0, 0.0),
        Vec3(0.0, -0.22, -1.0),
        1.3,
        2.0,
        width,
        height
    );
    Scene scene(camera, framebuffer);
    scene.set_background_gradient(Color::skyBlue(), Color::white());

    auto sphereShader = std::make_shared<LambertianShader>(Color::coral());
    auto floorShader = std::make_shared<LambertianShader>(Color::grey());

    scene.add_shape(std::make_shared<Sphere>(
        Vec3(0.0, -0.25, -3.5),
        0.75,
        sphereShader
    ));

    // Two triangles make a large horizontal floor with its normals facing up.
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(-10.0, -1.0, -1.0),
        Vec3(10.0, -1.0, -1.0),
        Vec3(10.0, -1.0, -10.0),
        floorShader
    ));
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(-10.0, -1.0, -1.0),
        Vec3(10.0, -1.0, -10.0),
        Vec3(-10.0, -1.0, -10.0),
        floorShader
    ));

    scene.add_light(std::make_shared<Light>(
        Vec3(-3.0, 5.0, -1.0),
        Color::white(),
        1.2
    ));
    scene.add_light(std::make_shared<Light>(
        Vec3(4.0, 2.0, -4.0),
        Color::white(),
        0.25
    ));

    scene.render("lambertian_sphere_floor.png");
    std::cout << "Rendered Lambertian sphere and floor to lambertian_sphere_floor.png\n";
    return 0;
}