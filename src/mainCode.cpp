#include "Camera/perspective_camera.h"
#include "Shader/blinnphong_shader.h"
#include "Shader/lambertian_shader.h"
#include "Shader/mirror_shader.h"
#include "Shader/normal_shader.h"
#include "Shape/scene.h"
#include "Shape/sphere.h"
#include "Shape/triangle.h"

#include <iostream>
#include <memory>

void CoolMirrorShader()
{
    constexpr int width = 2560;
    constexpr int height = 1440;

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

    auto sphereMirrorShader = std::make_shared<MirrorShader>(Color::white());
    auto sphereLambShader = std::make_shared<LambertianShader>(Color::red());
    auto floorShader = std::make_shared<LambertianShader>(Color::grey());

    scene.add_shape(std::make_shared<Sphere>(
        Vec3(0.0, -0.25, -3.5),
        0.75,
        sphereMirrorShader
    ));

    scene.add_shape(std::make_shared<Sphere>(
        Vec3(1.5, -0.25, -3.5),
        0.75,
        sphereMirrorShader
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
};


int main()
{   
    // constexpr int width = 2560;
    // constexpr int height = 1440;
    constexpr int width = 500;
    constexpr int height = 500;

    Vec3 camPos = Vec3(0.0, 3.0, 3.0);

    Framebuffer framebuffer(width, height);

    auto camera = std::make_shared<PerspectiveCamera>(
        camPos,
        Vec3(0.0, -0.4, -1.0),
        0.4,
        0.5,
        width,
        height
    );

    Scene scene(camera, framebuffer);
    scene.set_background_gradient(Color::skyBlue(), Color::white());

    // Top Left Light
    scene.add_light(std::make_shared<Light>(
        Vec3(-5, 8, 5),
        Color(0.7, 0.6, 0.45)
    ));
    // Top right Light
    scene.add_light(std::make_shared<Light>(
        Vec3(6, 6, 2),
        Color(0.35, 0.45, 0.7)
    ));
    
    // Floor
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(-50.0, 0.0, 50.0),
        Vec3(50.0, 0.0, 50.0),
        Vec3(50.0, 0.0, -50.0),
        std::make_shared<LambertianShader>(Color(0.6, 0.6, 0.6))
    ));
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(-50, 0.0, 50.0),
        Vec3(50.0, 0.0, -50.0),
        Vec3(-50.0, 0.0, -50.0),
        std::make_shared<LambertianShader>(Color(0.6, 0.6, 0.6))
    ));

    // Mirror Wall
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(-4, 0, -6),
        Vec3(4, 0, -6),
        Vec3(4, 4, -6),
        std::make_shared<MirrorShader>(Color::white())
    ));
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(-4, 0, -6),
        Vec3(4, 4, -6),
        Vec3(-4, 4, -6),
        std::make_shared<MirrorShader>(Color::white())
    ));

    // Floating Triangle
    scene.add_shape(std::make_shared<Triangle>(
        Vec3(0.9, 1.4, -0.6),
        Vec3(1.9, 1.4, -0.6),
        Vec3(1.4, 2.2, -1.1),
        std::make_shared<LambertianShader>(Color(0.9, 0.8, 0.1))
    ));

    // Green SPhere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(-2, 0.8, -3),
        0.8,
        std::make_shared<LambertianShader>(Color(0.2, 0.8, 0.2))
    ));

    // Red Blinn-Phong sphere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(-1.1, 0.6, -1.2),
        0.6,
        std::make_shared<BlinnPhongShader>(
            Color(0.8, 0.1, 0.1),
            camPos,
            Color(1.0, 1.0, 1.0),
            64.0
        )
    ));

    // Normal Sphere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(0.0, 0.9, -3.5),
        0.9,
        std::make_shared<NormalShader>()
    )); 

    // Blue Shphere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(0.3, 0.45, -1.6),
        0.45,
        std::make_shared<BlinnPhongShader>(
            Color(0.1, 0.2, 0.8),
            camPos,
            Color(1.0, 1.0, 1.0),
            16.0
        )
    ));

    // Mirror Sphere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(2.0, 1.0, -3.0),
        1.0,
        std::make_shared<MirrorShader>(Color::white())
    )); 

    // Front Mirror Sphere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(1.5, 0.5, 0.3),
        0.5,
        std::make_shared<MirrorShader>(Color::white())
    )); 

    // Diffuse Sphere
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(-1.3, 0.45, 0.4),
        0.45,
        std::make_shared<LambertianShader>(Color(0.2, 0.7, 0.7))
    ));

    // Behind Camera
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(0.3, 1.0, 5.0),
        1,
        std::make_shared<BlinnPhongShader>(
            Color(0.95, 0.5, 0.1),
            camPos,
            Color(1.0, 1.0, 1.0),
            32.0
        )
    ));
    scene.add_shape(std::make_shared<Sphere>(
        Vec3(2.4, 0.8, 4.8),
        0.8,
        std::make_shared<LambertianShader>(Color(0.6, 0.2, 0.8))
    ));

    scene.render("LabTest.png");
    std::cout << "Rendered to LabTest.png\n";

    return 0;
}   