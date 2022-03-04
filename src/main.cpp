#include <iostream>
#include <chrono>
#include <string>

#include "utils.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"


color ray_color(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;

    // if ray bounce limit exceded, no more light is gathered
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
    std::cerr << "C le RayonTraceur!!!" << std::endl;
    Timer execution("Execution"); 

    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    hittable_list world;
    
    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.4, 0.4));
    auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<dielectric>(1.5);
    auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100, material_ground)); 
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5, material_center)); 
    world.add(std::make_shared<sphere>(point3(-1.0,0,-1), -0.5, material_left)); 
    world.add(std::make_shared<sphere>(point3(1.0,0,-1), 0.5, material_right)); 

    // Camera
    camera cam(aspect_ratio, 2.0, 1.0);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j>=0 ; j--)
    {
        // progressbar
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i<image_width; i++ )
        {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = (i+random_double()) / (image_width-1);
                auto v = (j+random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << std::endl << "Done." << std::endl;
}