#pragma once

class camera
{
public:
    camera(
        point3 lookfrom, 
        point3 lookat, 
        vec3 vup, 
        float vfov, 
        float aspect_ratio,
        double aperture,
        double focus_dist)
        :origin(lookfrom), w(unit_vector(lookfrom - lookat)), u(unit_vector(cross(vup, w))), v(cross(w,u)), lens_radius(aperture/2)   
    {
        auto theta = deg_to_rad(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        /*
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w,u);

        lens_radius = aperture/2;
        */
       
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;
    }

    ray get_ray(double s, double t) const
    {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(
            origin + offset,
            lower_left_corner + s*horizontal + t*vertical - origin - offset);
    }

private:
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;
    vec3 w, u, v;
    double lens_radius;
};
