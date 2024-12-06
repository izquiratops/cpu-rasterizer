#pragma once

#include <rasterizer/renderer.hpp>
#include <algorithm>

namespace rasterizer 
{
    void clear(const image_view &color_buffer, const vector4f &color)
    {
        auto ptr = color_buffer.pixels;
        auto size = color_buffer.width * color_buffer.height;
        std::fill_n(ptr, size, to_color4ub(color));
    }
}