#ifndef SCENE_H
#define SCENE_H

#include "shape.h"
#include "ray.h"
#include "color.h"
#include "../Light/light.h"
#include "Framebuffer.h"
#include "../Camera/camera.h"
#include "../Shape/hitrecord.h"

#include <cstddef>
#include <memory>
#include <vector>
#include <string>

using namespace std;
using std::make_shared;
using std::shared_ptr;

class Scene {
public:
        Scene(std::shared_ptr<Camera> camera, Framebuffer framebuffer): cam(camera), framebuffer(framebuffer) {}

        void add_shape(std::shared_ptr<Shape> shape);

        void add_light(std::shared_ptr<Light> light);

        void set_background_gradient(const Color& top, const Color& bottom);

        // this should eventually be replaced by a sky class or smth :)
        Color render_background_color(const Ray& ray) const;

        Color computeRayColor(Ray ray, int minBounces = 0, int maxBounces = 5);

        void render(string exportName);


        Framebuffer framebuffer;
        std::shared_ptr<Camera> cam;
        std::vector<std::shared_ptr<Shape>> shapes;
        std::vector<std::shared_ptr<Light>> lights;

    private:
        struct BVHEntry {
            std::shared_ptr<Shape> shape;
            Aabb bounds;
            std::size_t originalIndex;
        };

        struct BVHNode {
            Aabb bounds;
            std::shared_ptr<BVHNode> left;
            std::shared_ptr<BVHNode> right;
            std::vector<BVHEntry> leafShapes;
        };

        std::shared_ptr<BVHNode> buildBVH(
            std::vector<BVHEntry>& entries,
            std::size_t begin,
            std::size_t end);
        bool intersectBVH(
            const BVHNode* node,
            const Ray& ray,
            double t_min,
            double t_max,
            double& closest_so_far,
            std::size_t& closest_shape_index,
            HitRecord& rec) const;
        bool intersectShapes(
            const Ray& ray,
            double t_min,
            double t_max,
            HitRecord& rec);
        void rebuildBVH();

        std::shared_ptr<BVHNode> bvhRoot;
        std::vector<BVHEntry> unboundedShapes;
        bool bvhDirty = true;

        Color background_top = Color::white();
        Color background_bottom = Color::skyBlue();
};

#endif