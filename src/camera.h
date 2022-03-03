#pragma once

class camera
{
public:
    camera(float aspect_ratio, float viewport_height, float focal_length)
        :origin(0,0,0), 
        horizontal(aspect_ratio*viewport_height, 0, 0),
        vertical(0,viewport_height,0),
        lower_left_corner(origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length))
    {
    }

    ray get_ray(double u, double v) const
    {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

private:
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;
};
