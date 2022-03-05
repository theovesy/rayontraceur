#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>
#include <chrono>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility

struct Timer
{
    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer()
        : name("Timer"), start(std::chrono::steady_clock::now())
    {
    }

    Timer(const std::string& name)
        : name(name), start(std::chrono::steady_clock::now())
    {
    }

    ~Timer()
    {
        end = std::chrono::steady_clock::now();
        duration = end-start;

        std::cerr << name << " took " << duration.count() << "s" << std::endl;
    }
};

inline double deg_to_rad(double deg)
{
    return deg * pi / 180;
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}