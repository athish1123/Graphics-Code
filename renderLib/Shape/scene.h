#ifndef SCENE_H
#define SCENE_H

#include "shape.h"
#include "ray.h"
#include "color.h"
#include "../Light/light.h"
#include "Framebuffer.h"
#include "../Camera/camera.h"
#include "../Shape/hitrecord.h"


#include <memory>
#include <vector>
#include <string>

using namespace std;
using std::make_shared;
using std::shared_ptr;

class Scene {
public:
        Scene(std::shared_ptr<Camera> camera, Framebuffer framebuffer): cam(camera), framebuffer(framebuffer) {}

        void add_shape(std::shared_ptr<Shape> shape) {
            shapes.push_back(shape);
        }

        void add_light(std::shared_ptr<Light> light) {
            lights.push_back(light);
        }

        void set_background_gradient(const Color& top, const Color& bottom) {
            background_top = top;
            background_bottom = bottom;
        }

        // this should eventually be replaced by a sky class or smth :)
        Color render_background_color(const Ray& ray) const {
            Vec3 unit_direction = normalize(ray.getDirection());
            double t = 0.5 * (unit_direction.y() + 1.0);
            return Color::fromVec3((1.0 - t) * background_bottom + t * background_top);
        }

        void render(string exportName) {
            Ray ray;
            HitRecord rec;
            double t_min = 0.001;
            double t_max = std::numeric_limits<double>::infinity();

            HitRecord temp_rec;
            bool hit_anything = false;
            auto closest_so_far = t_max;

            for (int x = 0; x < framebuffer.getImageWidth(); ++x) {
                for (int y = 0; y < framebuffer.getImageHeight(); ++y) {

                    cam->generateRay(x, y, ray);

                    temp_rec = HitRecord();
                    hit_anything = false;
                    closest_so_far = t_max;

                    // iterate thru all known shapes and calc intersect
                    for (const auto& shape : shapes) {
                        if (shape->intersect(ray, t_min, closest_so_far, temp_rec)) {
                            hit_anything = true;
                            closest_so_far = temp_rec.t;
                            rec = temp_rec;
                        }
                    }
                    
                    // render whatever we hit
                    if (hit_anything) {
                        framebuffer.setPixelColor(x, y, rec.shader->render(rec.point, rec.normal, lights));
                    } else {
                        // render_background_color(ray) should eventually be replaced with sky.render(ray)
                        // so that we can pass in a sky obj and get any effect back out
                        framebuffer.setPixelColor(x, y, render_background_color(ray));
                    }
                }
            }
            
            framebuffer.exportAsPNG(exportName);
        }


        Framebuffer framebuffer;
        std::shared_ptr<Camera> cam;
        std::vector<std::shared_ptr<Shape>> shapes;
        std::vector<std::shared_ptr<Light>> lights;

    private:
        Color background_top = Color::white();
        Color background_bottom = Color::skyBlue();
};

#endif