#pragma once
#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(point3 cen, double r, std::shared_ptr<material> m) 
        : m_center(cen), m_radius(r), mat_ptr(m) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
    {
        vec3 oc = r.origin() - m_center;
        double a = r.direction().norm_squared();
        double half_b = dot(oc, r.direction());
        double c = oc.norm_squared() - m_radius*m_radius;

        double discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        double sqrtd = sqrt(discriminant); 

        // find the nearest root that lies in the acceptable range.
        double root = (-half_b - sqrtd) / a;
        if (t_max < root || root < t_min)
        {
            root = (-half_b + sqrtd) / a;
            if (t_max < root || root < t_min)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - m_center) / m_radius;
        vec3 outward_normal = (rec.p - m_center) / m_radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;

        return true;
    }

public:
    std::shared_ptr<material> mat_ptr;
private:
    point3 m_center;
    double m_radius;
};