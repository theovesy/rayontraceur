#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "vec3.h"

class Image
{
public:
    Image(int width, int height);

public:
    color get_color(int x, int y) const;
    void set_color(const color& pixel_color, int x, int y);

    void export_image(const char* path) const;

private:
    int m_width;
    int m_height;
    std::vector<color> m_colors;
};

Image::Image(int width, int height) 
    : m_width(width), m_height(height), m_colors(std::vector<color>(width * height)) {}

color Image::get_color(int x, int y) const
{
    return m_colors[y * m_width + x];
}

void Image::set_color(const color& pixel_color, int x, int y)
{   
    m_colors[y * m_width + x] = color(pixel_color.x(), pixel_color.y(), pixel_color.z());
}

void Image::export_image(const char* path) const
{
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open())
        std::cerr << "file could not be opened" << std::endl;
    
    unsigned char bmp_pad[3] = {0,0,0};
    const int padding_amount = ((4 - (m_width * 3) % 4) %4);

    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size = file_header_size + information_header_size + m_width * m_width * 3 + padding_amount * m_width;

    unsigned char file_header[file_header_size];

    // File type
    file_header[0] = 'B';
    file_header[1] = 'M';
    // File size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    // Reserved 1 (not used)
    file_header[6] = 0;
    file_header[7] = 0;
    // Reserved 2 (not used)
    file_header[8] = 0;
    file_header[9] = 0;
    // Pixel data offset
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    // Header size
    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    // Image width
    information_header[4] = m_width;
    information_header[5] = m_width >> 8;
    information_header[6] = m_width >> 16;
    information_header[7] = m_width >> 24;
    // Image height 
    information_header[8] = m_height;
    information_header[9] = m_height >> 8;
    information_header[10] = m_height >> 16;
    information_header[11] = m_height >> 24;
    // Planes
    information_header[12] = 1;
    information_header[13] = 0;
    // Bits per pixel (RGB)
    information_header[14] = 24;
    information_header[15] = 0;
    // Compression (no compression)
    for (int i = 16; i < information_header_size; i++)
        information_header[i] = 0;

    f.write(reinterpret_cast<char*>(file_header), file_header_size);
    f.write(reinterpret_cast<char*>(information_header), information_header_size);

    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            unsigned char r = static_cast<unsigned char>(get_color(i, j).x());
            unsigned char g = static_cast<unsigned char>(get_color(i, j).y());
            unsigned char b = static_cast<unsigned char>(get_color(i, j).z());

            unsigned char pixel_color[] = {b,g,r};

            f.write(reinterpret_cast<char*>(pixel_color), 3);
        }

        f.write(reinterpret_cast<char*>(bmp_pad), padding_amount);
    }

    f.close();

    std::cerr << "image written\n"; 
}