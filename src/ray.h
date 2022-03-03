#pragma once

#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : m_origin(origin), m_dir(direction)
    {}

public:
    point3 origin() const { return m_origin; }
    vec3 direction() const { return m_dir; }

    point3 at(double t) const 
    {
        return m_origin + t*m_dir;
    }

private:
    point3 m_origin;
    vec3 m_dir;
};
