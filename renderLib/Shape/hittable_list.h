#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class Hittable_list : public Hittable {
  public:
    std::vector<shared_ptr<Hittable>> objects;

    Hittable_list() {}
    Hittable_list(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool intersect(const Ray& ray, double t_min, double t_max, HitRecord& hit) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object : objects) {
            if (object->intersect(ray, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.rayHitParameter;
                hit = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif