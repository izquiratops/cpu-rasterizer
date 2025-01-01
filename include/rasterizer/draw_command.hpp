#pragma once

#include <rasterizer/mesh.hpp>
#include <rasterizer/settings.hpp>

namespace rasterizer {
struct draw_command {
  struct mesh mesh;
  enum cull_mode cull_mode = cull_mode::none;
};
}  // namespace rasterizer