#include "scene.h"
#include "../Shader/mirror_shader.h"

#include <limits>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <omp.h>

void Scene::add_shape(std::shared_ptr<Shape> shape)
{
    shapes.push_back(shape);
    bvhDirty = true;
}

void Scene::add_light(std::shared_ptr<Light> light)
{
    lights.push_back(light);
}

void Scene::set_background_gradient(const Color& top, const Color& bottom)
{
    background_top = top;
    background_bottom = bottom;
}

std::shared_ptr<Scene::BVHNode> Scene::buildBVH(
    std::vector<BVHEntry>& entries,
    std::size_t begin,
    std::size_t end)
{
    constexpr std::size_t leafSize = 4;
    auto node = std::make_shared<BVHNode>();
    node->bounds = entries[begin].bounds;
    for (std::size_t i = begin + 1; i < end; ++i) {
        node->bounds = Aabb::surroundingBox(node->bounds, entries[i].bounds);
    }

    if (end - begin <= leafSize) {
        node->leafShapes.reserve(end - begin);
        for (std::size_t i = begin; i < end; ++i) {
            node->leafShapes.push_back(entries[i]);
        }
        return node;
    }

    Aabb centroidBounds(
        entries[begin].bounds.centroid(),
        entries[begin].bounds.centroid());
    for (std::size_t i = begin + 1; i < end; ++i) {
        const Vec3 centroid = entries[i].bounds.centroid();
        centroidBounds = Aabb::surroundingBox(centroidBounds, Aabb(centroid, centroid));
    }

    const Vec3 centroidExtent = centroidBounds.extent();
    int axis = 0;
    if (centroidExtent.y() > centroidExtent.x()) {
        axis = 1;
    }
    if (centroidExtent.z() > centroidExtent[axis]) {
        axis = 2;
    }

    const std::size_t middle = begin + (end - begin) / 2;
    std::nth_element(
        entries.begin() + begin,
        entries.begin() + middle,
        entries.begin() + end,
        [axis](const BVHEntry& left, const BVHEntry& right) {
            const double leftCentroid = left.bounds.centroid()[axis];
            const double rightCentroid = right.bounds.centroid()[axis];
            if (leftCentroid == rightCentroid) {
                return left.originalIndex < right.originalIndex;
            }
            return leftCentroid < rightCentroid;
        });

    node->left = buildBVH(entries, begin, middle);
    node->right = buildBVH(entries, middle, end);
    return node;
}

void Scene::rebuildBVH()
{
    std::vector<BVHEntry> boundedShapes;
    boundedShapes.reserve(shapes.size());
    unboundedShapes.clear();

    for (std::size_t i = 0; i < shapes.size(); ++i) {
        Aabb bounds;
        if (shapes[i]->bounding_box(bounds)) {
            boundedShapes.push_back({shapes[i], bounds, i});
        } else {
            unboundedShapes.push_back({shapes[i], bounds, i});
        }
    }

    bvhRoot = boundedShapes.empty()
        ? nullptr
        : buildBVH(boundedShapes, 0, boundedShapes.size());
    bvhDirty = false;
}

bool Scene::intersectBVH(
    const BVHNode* node,
    const Ray& ray,
    double t_min,
    double t_max,
    double& closest_so_far,
    std::size_t& closest_shape_index,
    HitRecord& rec) const
{
    if (!node || !node->bounds.hit(ray, t_min, closest_so_far)) {
        return false;
    }

    bool hit_anything = false;
    HitRecord temp_rec;
    if (!node->leafShapes.empty()) {
        for (const auto& entry : node->leafShapes) {
            const double upperBound = closest_so_far < t_max
                ? std::min(t_max, std::nextafter(closest_so_far, std::numeric_limits<double>::infinity()))
                : t_max;
            if (entry.shape->intersect(ray, t_min, upperBound, temp_rec)
                && (temp_rec.t < closest_so_far
                    || (temp_rec.t == closest_so_far && entry.originalIndex < closest_shape_index))) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                closest_shape_index = entry.originalIndex;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }

    if (intersectBVH(node->left.get(), ray, t_min, t_max, closest_so_far, closest_shape_index, rec)) {
        hit_anything = true;
    }
    if (intersectBVH(node->right.get(), ray, t_min, t_max, closest_so_far, closest_shape_index, rec)) {
        hit_anything = true;
    }
    return hit_anything;
}

bool Scene::intersectShapes(
    const Ray& ray,
    double t_min,
    double t_max,
    HitRecord& rec)
{
    if (bvhDirty) {
        rebuildBVH();
    }

    bool hit_anything = false;
    double closest_so_far = t_max;
    std::size_t closest_shape_index = std::numeric_limits<std::size_t>::max();
    HitRecord temp_rec;

    for (const auto& entry : unboundedShapes) {
        const double upperBound = closest_so_far < t_max
            ? std::min(t_max, std::nextafter(closest_so_far, std::numeric_limits<double>::infinity()))
            : t_max;
        if (entry.shape->intersect(ray, t_min, upperBound, temp_rec)
            && (temp_rec.t < closest_so_far
                || (temp_rec.t == closest_so_far && entry.originalIndex < closest_shape_index))) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            closest_shape_index = entry.originalIndex;
            rec = temp_rec;
        }
    }

    if (intersectBVH(
            bvhRoot.get(),
            ray,
            t_min,
            t_max,
            closest_so_far,
            closest_shape_index,
            rec)) {
        hit_anything = true;
    }

    return hit_anything;
}

Color Scene::render_background_color(const Ray& ray) const
{
    Vec3 unit_direction = normalize(ray.getDirection());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return Color::fromVec3((1.0 - t) * background_bottom + t * background_top);
}

Color Scene::computeRayColor(Ray ray, int minBounces, int maxBounces)
{
    constexpr double rayEpsilon = 0.001;

    HitRecord rec;
    bool hit_anything = false;
    double t_min = 0.001;
    double t_max = std::numeric_limits<double>::infinity();
    hit_anything = intersectShapes(ray, t_min, t_max, rec);

    if (!hit_anything) {
        return render_background_color(ray);
    }

    const auto mirrorShader = std::dynamic_pointer_cast<MirrorShader>(rec.shader);
    if (mirrorShader) {
        if (minBounces >= maxBounces) {
            return Color::black();
        }

        const Vec3 unitDirection = normalize(ray.getDirection());
        const Vec3 unitNormal = normalize(rec.normal);
        const Vec3 reflectedDirection =
            unitDirection - 2.0 * dot(unitDirection, unitNormal) * unitNormal;
        const Vec3 reflectedOrigin = rec.point
            + (dot(reflectedDirection, unitNormal) >= 0.0 ? rayEpsilon : -rayEpsilon) * unitNormal;
        const Ray reflectedRay(reflectedOrigin, reflectedDirection);

        return Color::fromVec3(
            mirrorShader->getTint() * computeRayColor(reflectedRay, minBounces + 1, maxBounces));
    }

    constexpr double shadowEpsilon = 0.001;

    // Per-thread reusable buffer: no heap alloc per pixel, no shared_ptr refcount traffic.
    thread_local std::vector<const Light*> visibleLights;
    visibleLights.clear();

    for (const auto& light : lights) {
        if (!light) {
            continue;
        }

        Vec3 toLight = light->position - rec.point;
        if (toLight.length_squared() < shadowEpsilon * shadowEpsilon) {
            continue;
        }

        const double normalSide = dot(rec.normal, toLight);
        const Vec3 shadowOrigin = rec.point
            + (normalSide >= 0.0 ? shadowEpsilon : -shadowEpsilon) * normalize(rec.normal);
        toLight = light->position - shadowOrigin;
        const double lightDistance = toLight.length();
        if (lightDistance <= shadowEpsilon) {
            visibleLights.push_back(light.get());
            continue;
        }

        const Ray shadowRay(shadowOrigin, toLight / lightDistance);
        bool blocked = false;
        HitRecord shadowHit;
        blocked = intersectShapes(
            shadowRay,
            shadowEpsilon,
            lightDistance - shadowEpsilon,
            shadowHit);

        if (!blocked) {
            visibleLights.push_back(light.get());
        }
    }

    return rec.shader->render(rec.point, rec.normal, visibleLights);
}

void Scene::render(string exportName)
{
    if (bvhDirty) {
        rebuildBVH();
    }

    const int samplesPerSide = 2;
    const int totalSamples = samplesPerSide * samplesPerSide;
    const int width = framebuffer.getImageWidth();
    const int height = framebuffer.getImageHeight();

    double t0 = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vec3 pixelColor(0.0, 0.0, 0.0);

            for (int py = 0; py < samplesPerSide; ++py) {
                for (int px = 0; px < samplesPerSide; ++px) {
                    double offsetX = (static_cast<double>(px) + 0.5) / samplesPerSide - 0.5;
                    double offsetY = (static_cast<double>(py) + 0.5) / samplesPerSide - 0.5;

                    Ray ray;
                    cam->generateRay(x, y, ray, offsetX, offsetY);

                    pixelColor += computeRayColor(ray);
                }
            }

            framebuffer.setPixelColor(x, y, pixelColor / static_cast<double>(totalSamples));
        }
    }

    std::cout << "render: " << omp_get_wtime() - t0 << "s\n";

    framebuffer.exportAsPNG(exportName);
}