#pragma once

#include "vec3.h"
#include <memory>
#include <vector>

class material;

struct hit_record
{
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

class hittable_list : public hittable
{
public: 
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object)
    {
        add(object);
    }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) 
    {
        objects.push_back(object);
    }

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto& object : objects)
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

private:
    std::vector<std::shared_ptr<hittable>> objects;
};