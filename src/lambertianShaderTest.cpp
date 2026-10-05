#include "Camera/perspective_camera.h"
#include "Shader/lambertian_shader.h"
#include "Shape/sphere.h"
#include "framebuffer.h"
#include "Shape/triangle.h"
#include "Shape/scene.h"

#include <iostream>
#include <limits>

#include "Shader/lambertian_shader.h"

#include<iostream>


// void render_funny_triangles() {
//     Framebuffer framebuffer(200, 200);

//     PerspectiveCamera cam(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0), framebuffer.getImageWidth(), framebuffer.getImageHeight(), 1.0, 0.5);

//     Scene scene = Scene(make_shared<PerspectiveCamera>(cam), framebuffer);

//     scene.set_background_gradient( Color::skyBlue(), Color::white() );
//     std::shared_ptr<Shader> normal_shader = std::make_shared<NormalShader>();
//     // std::shared_ptr<Shader> lambertian_shader = std::make_shared<LambertianShader>(Color::red());

//     Tri tri1( Vec3(0.773205, -0.93923, -7), Vec3(0.0330127, 0.94282, -5), Vec3(-0.45, 0.779423, -5), std::make_shared<LambertianShader>(Color::red()) );
//     Tri tri2( Vec3(0.426795, 1.13923, -7), Vec3(-0.833013, -0.44282, -5), Vec3(-0.45, -0.779423, -5), std::make_shared<LambertianShader>(Color::green()) );
//     Tri tri3( Vec3(-1.2, -0.2, -7), Vec3(0.8, -0.5, -5), Vec3(0.9, 0, -5), std::make_shared<LambertianShader>(Color::blue()) );
//     Sphere sphere1 = Sphere( Vec3(0.0, 0.0, -6.0), 0.2, std::make_shared<LambertianShader>(Color::purple()) );
//     Light light = Light( Vec3(0.0, 3.0, -2.0), Color::white(), 1.0 );
//     Light light2 = Light( Vec3(0.0, -2.0, -4.0), Color::white(), 1.0 );

//     // adding shapes
//     scene.add_shape(make_shared<Triangle>(tri1));
//     scene.add_shape(make_shared<Triangle>(tri2));
//     scene.add_shape(make_shared<Triangle>(tri3));
//     scene.add_shape(make_shared<Sphere>(sphere1));

//     // adding lights
//     scene.add_light( make_shared<Light>(light));
//     scene.add_light(make_shared<Light>(light2));

//     scene.render();
// }


// void render_lambert_test_scene() {
//     Framebuffer framebuffer(200, 200);

//     PerspectiveCamera cam(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0), framebuffer.getImageWidth(), framebuffer.getImageHeight(), 1.0, 0.5);

//     Scene scene = Scene(make_shared<PerspectiveCamera>(cam), framebuffer);

//     scene.set_background_gradient( Color::skyBlue(), Color::white() );
//     // std::shared_ptr<Shader> normal_shader = std::make_shared<NormalShader>();
//     std::shared_ptr<Shader> lambertian_shader = std::make_shared<LambertianShader>(Color::red());

//     Sphere sphere1 = Sphere( Vec3(0.0, 0.0, -6.0), 1.0, std::make_shared<LambertianShader>(Color::purple()) );
//     Sphere sphere2 = Sphere( Vec3(0.0, -2.0, -5.0), 6.0, std::make_shared<LambertianShader>(Color::skyBlue()) );
//     // Sphere sphere3 = Sphere( Vec3(0.0, 0.0, -6.0), 1.0, std::make_shared<LambertianShader>(Color::purple()) );

//     Light light = Light( Vec3(0.0, 3.0, -2.0), Color::white(), 1.0 );
//     Light light2 = Light( Vec3(0.0, -2.0, -4.0), Color::white(), 1.0 );

//     // adding shapes
//     scene.add_shape(make_shared<Sphere>(sphere1));
//     scene.add_shape(make_shared<Sphere>(sphere2));

//     // adding lights
//     scene.add_light( make_shared<Light>(light));
//     scene.add_light(make_shared<Light>(light2));

//     scene.render();
// }

int main(int argc, char** argv) {

    Framebuffer framebuffer(800, 800);

    PerspectiveCamera cam(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0), 1.0, 0.5, framebuffer.getImageWidth(), framebuffer.getImageHeight());

    Scene scene = Scene(make_shared<PerspectiveCamera>(cam), framebuffer);

    scene.set_background_gradient( Color::skyBlue(), Color::white() );

    Sphere sphere1 = Sphere( Vec3(0.0, 0.0, -6.0), 1.0, std::make_shared<LambertianShader>( Color::mint()) );
    Sphere sphere2 = Sphere( Vec3(0.5, -0.5, -5.0), 0.2, std::make_shared<LambertianShader>( Color::lavender()) );
    Sphere sphere3 = Sphere( Vec3(-0.5, -0.5, -4.0), 0.2, std::make_shared<LambertianShader>( Color::coral()) );

    Light light = Light( Vec3(2.0, -4.0, 2.0), Color::indigo(), 1.0 );
    Light light2 = Light( Vec3(-2.0, 4.0, -2.0), Color::white(), 1.0 );
    Light light3 = Light( Vec3(0.0, 4.0, 0.0), Color::pink(), 1.0 );
    Light light4 = Light( Vec3(10.0, -12.0, -20.0), Color::red(), 2.0 );
    Light light5 = Light( Vec3(-10.0, 12.0, -20.0), Color::yellow(), 1.0 );

    // adding shapes
    scene.add_shape(make_shared<Sphere>(sphere1));
    scene.add_shape(make_shared<Sphere>(sphere2));
    scene.add_shape(make_shared<Sphere>(sphere3));

    // adding lights
    scene.add_light( make_shared<Light>(light));
    scene.add_light(make_shared<Light>(light2));
    scene.add_light(make_shared<Light>(light3));
    scene.add_light(make_shared<Light>(light4));
    scene.add_light(make_shared<Light>(light5));

    scene.render("Lamebrsion2.png");
	// framebuffer.exportAsPNG("meow");
	cout << "works";
}