#ifndef MATERIAL
#define MATERIAL

#include "geometry.h"

struct Material
{
    Vec2f albedo;
    Vec3f diffuse_color;
    float specular_exponent;

    Material(const Vec3f &color) : diffuse_color(color) {}
    Material(const Vec2f &a, const Vec3f &color, const float &spec) : albedo(a), diffuse_color(color), specular_exponent(spec) {}
    Material() : albedo(1,0), diffuse_color(), specular_exponent() {}
};

struct Material3f
{
    Vec3f albedo;
    Vec3f diffuse_color;
    float specular_exponent;

    Material3f(const Vec3f &a, const Vec3f &color, const float &spec) : albedo(a), diffuse_color(color), specular_exponent(spec) {}
    Material3f() : albedo(1, 0, 0), diffuse_color(), specular_exponent() {}
};

#endif // MATERIAL

