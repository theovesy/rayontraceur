#pragma once

#include "vec3.h"
#include <iostream>
#include <cstdint>
#include <fstream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // divide the color by the number of samples
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // write the translated [0,255] value of each color compoment;
    out << static_cast<int>(256 * clamp(r,0.0,0.999)) << ' '
        << static_cast<int>(256 * clamp(g,0.0,0.999)) << ' '
        << static_cast<int>(256 * clamp(b,0.0,0.999)) << "\n"; 
}

color* better_colors_thanks(color& pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // divide the color by the number of samples
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    color* new_pixel = new color(256 * clamp(r,0.0,0.999),256 * clamp(g,0.0,0.999),256 * clamp(b,0.0,0.999));

    return new_pixel;
}

