#include <iostream>
#include "vec3.h"
#include "framebuffer.h"
#include "Camera/perspective_camera.h"
#include "Shape/sphere.h"
#include "Shape/triangle.h"
#include <cmath>
#include "Shape/hittable_list.h"

using namespace std;


Vec3 ray_color_sphere(const Ray& r, Sphere& sphere)
{
    HitRecord hit;
    if (sphere.intersect(r, 0.001, INFINITY, hit))
        return 0.5 * (hit.surfaceNormal + Vec3(1, 1, 1));
    else
    {
        return Vec3(0, 1, 0);
    }


    // Vec3 dir = r.getDirection();
    // dir = normalize(dir); 
    // Vec3 ray_dir_color = (dir + Vec3(1,1,1)) * 0.5;
    // return ray_dir_color;
}

Vec3 ray_color(const Ray& r, const Hittable& world)
{
    HitRecord hit;
    if (world.intersect(r, 0.001, INFINITY, hit))
        return 0.5 * (hit.surfaceNormal + Vec3(1, 1, 1));
    return Vec3(0, 0, 0);
}

int main()
{
    Framebuffer fb(200,200);
    PerspectiveCamera pCamera(Vec3(0,0,0), Vec3(0,0,-1), 1.3, 2.0, fb.getImageWidth(), fb.getImageHeight());
    // Sphere sphere(Point3(0,0,-2), 0.5);
    // Triangle tri(Point3(0, 0, -1), Point3(0.5, -0.5, -1), Point3(0, 0.5, -1));

    Hittable_list world;
    // world.add(make_shared<Triangle>(Point3(-0.5,-0.5,-1), Point3(0.5,-0.5,-1), Point3(0,0.5,-1)));
    // world.add(make_shared<Triangle>(Point3(0.2,-0.2,-0.8), Point3(1,-0.2,-0.8), Point3(0.6,0.6,-0.8)));
    // world.add(make_shared<Sphere>(Point3(-0.8,0,-1.5), 0.3));

    world.add(make_shared<Triangle>(Point3(-1,-0.5,-0.5), Point3(1,-0.5,-0.5), Point3(0,-0.5,-2)));
    world.add(make_shared<Sphere>(Point3(0,-0.2,-1), 0.3));

    for(int j = 0; j < fb.getImageHeight(); j++)
    {
        for(int i = 0; i < fb.getImageWidth(); i++)
        {
            Ray r;
            int flippedJ = fb.getImageHeight() - 1 - j;
            pCamera.generateRay(i, flippedJ, r);
            fb.setPixelColor(i, j, ray_color(r, world));
        } 
    }
    fb.exportAsPNG("Sphere.png");
    cout << "works";
}