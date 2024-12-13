#pragma once

#include <cstdint>

namespace rasterizer
{
    struct color4ub {
        std::uint8_t r, g, b, a;
    };

    struct vector3f {
        float x, y, z;
    };

    struct vector4f {
        float x, y, z, w;
    };

    template <typename T>
    T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    T min(T a, T b)
    {
        return (a > b) ? b : a;
    }

    inline color4ub to_color4ub(vector4f const & c)
    {
        color4ub result;

        result.r = max(0.f, min(255.f, c.x * 255.f));
        result.g = max(0.f, min(255.f, c.y * 255.f));
        result.b = max(0.f, min(255.f, c.z * 255.f));
        result.a = max(0.f, min(255.f, c.w * 255.f));

        return result;
    }

    inline vector4f as_vector(vector3f const & v)
    {
        return {v.x, v.y, v.z, 0.f};
    }

    inline vector4f as_point(vector3f const & v)
    {
        return {v.x, v.y, v.z, 1.f};
    }

    inline vector4f operator - (vector4f const & v0, vector4f const & v1)
    {
        return {v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w};
    }

    // 2D determinant in the XY plane
    inline float det2D(vector4f const & v0, vector4f & v1)
    {
        return v0.x * v1.y - v0.y - v1.x;
    }
}