#include "scene.h"

#include <limits>

void Scene::add_shape(std::shared_ptr<Shape> shape)
{
    shapes.push_back(shape);
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

Color Scene::render_background_color(const Ray& ray) const
{
    Vec3 unit_direction = normalize(ray.getDirection());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return Color::fromVec3((1.0 - t) * background_bottom + t * background_top);
}

Color Scene::computeRayColor(Ray ray)
{
    HitRecord rec;
    HitRecord temp_rec;
    bool hit_anything = false;
    double t_min = 0.001;
    double t_max = std::numeric_limits<double>::infinity();
    auto closest_so_far = t_max;

    for (const auto& shape : shapes) {
        if (shape->intersect(ray, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    if (hit_anything) {
        constexpr double shadowEpsilon = 0.001;
        std::vector<std::shared_ptr<Light>> visibleLights;
        visibleLights.reserve(lights.size());

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
                visibleLights.push_back(light);
                continue;
            }

            const Ray shadowRay(shadowOrigin, toLight / lightDistance);
            bool blocked = false;
            for (const auto& shape : shapes) {
                if (shape->intersect(shadowRay, shadowEpsilon, lightDistance - shadowEpsilon, temp_rec)) {
                    blocked = true;
                    break;
                }
            }

            if (!blocked) {
                visibleLights.push_back(light);
            }
        }

        return rec.shader->render(rec.point, rec.normal, visibleLights);
    } else {
        return render_background_color(ray);
    }
}

void Scene::render(string exportName)
{
    const int samplesPerSide = 2;
    const int totalSamples = samplesPerSide * samplesPerSide;

    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < framebuffer.getImageHeight(); ++y) {
        for (int x = 0; x < framebuffer.getImageWidth(); ++x) {
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

    framebuffer.exportAsPNG(exportName);
}
