#include <algorithm>

#include <rasterizer/renderer.hpp>

namespace rasterizer {
void clear(image_view const &color_buffer, vector4f const &color) {
  auto ptr = color_buffer.pixels;
  auto size = color_buffer.width * color_buffer.height;
  std::fill_n(ptr, size, to_color4ub(color));
}

void draw(image_view const &color_buffer, draw_command const &command) {
  for (std::uint32_t vertex_index = 0;
       vertex_index + 2 < command.mesh.vertex_count; vertex_index += 3) {
    auto v0 = as_point(command.mesh.positions[vertex_index + 0]);
    auto v1 = as_point(command.mesh.positions[vertex_index + 1]);
    auto v2 = as_point(command.mesh.positions[vertex_index + 2]);

    for (std::int32_t y = 0; y < color_buffer.height; ++y) {
      for (std::int32_t x = 0; x < color_buffer.width; ++x) {
        vector4f p{x + 0.5f, y + 0.5f, 0.f, 0.f};
        
        float det01p = det2D(v1 - v0, p - v0);
        float det12p = det2D(v2 - v1, p - v1);
        float det20p = det2D(v0 - v2, p - v2);

        if (det01p >= 0.f && det12p >= 0.f && det20p >= 0.f)
        {
          color_buffer.at(x, y) = to_color4ub(command.mesh.color);
        }
      }
    }
  }
}
} // namespace rasterizer