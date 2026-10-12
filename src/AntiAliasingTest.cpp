
#include <iostream>
#include <memory>

#include "color.h"
#include "Shape/scene.h"
#include "Camera/perspective_camera.h"
#include "Shape/sphere.h"
#include "Shader/lambertian_shader.h"


void render_anti_testing()
{
    const int width = 800;
    const int height = 800;

    Framebuffer framebuffer(width, height);
    auto camera = std::make_shared<PerspectiveCamera>(
        Vec3(0.0, 0.0, 0.0),
        Vec3(0.0, 0.0, -1.0),
        1.3,
        2.0,
        width,
        height
    );

    Scene scene(camera, framebuffer);
    // scene.add_shape(std::make_shared<Sphere>(Color::blue()));

    // scene.add_shape(std::make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.45));
    Sphere sphere2 = Sphere(Vec3(0.0, 0.0, -1.0), 0.45, std::make_shared<LambertianShader>(Color::green()));
    // Place the light on the camera side of the sphere (positive z).
    Light key = Light(Vec3(0.0, 3.0, 0.0), Color::white(), 1.0);

    scene.add_shape(make_shared<Sphere>(sphere2));
    scene.add_light(make_shared<Light>(key));

    scene.set_background_gradient(Color::skyBlue(), Color::white());
    scene.render("antiAliasingTest.png");

    std::cout << "Rendered anti-aliasing test to antiAliasingTest.png" << std::endl;
}

int main()
{
    render_anti_testing();
    return 0;
}