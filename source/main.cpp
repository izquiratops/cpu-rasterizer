#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <rasterizer/renderer.hpp>

int main(int argv, char **args) {
  // std::cout now has its own separate buffer. this buffer too, when flushed, 
  // writes the characters to the device associated with stdout.
  // https://cplusplus.com/forum/beginner/140381/
  std::ios_base::sync_with_stdio( false ) ;

  SDL_Init(SDL_INIT_VIDEO);

  int width = 800;
  int height = 600;

  SDL_Window *window = SDL_CreateWindow(
      "My first rasterizer!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  SDL_Surface *draw_surface = nullptr;

  int mouse_x = 0;
  int mouse_y = 0;

  using clock = std::chrono::high_resolution_clock;

  auto last_frame_start = clock::now();

  bool running = true;
  while (running) {
    // Handle events, such as closing the window, or moving the mouse, etc.
    for (SDL_Event event; SDL_PollEvent(&event);)
      switch (event.type) {
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
        case SDL_WINDOWEVENT_RESIZED:
          if (draw_surface)
            SDL_FreeSurface(draw_surface);
          draw_surface = nullptr;
          width = event.window.data1;
          height = event.window.data2;
          break;
        }
        break;

      case SDL_QUIT:
        running = false;
        break;

      case SDL_MOUSEMOTION:
        mouse_x = event.motion.x;
        mouse_y = event.motion.y;
        break;
      }

    if (!running)
      break;

    if (!draw_surface) {
      // RGBA32 means 8 bits per channel, 32 bits total.
      draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
                                                    SDL_PIXELFORMAT_RGBA32);
      // Fully opaque pixels.
      SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_BLEND);
    }

    auto now = clock::now();
    float dt = std::chrono::duration_cast<std::chrono::duration<float>>(now - last_frame_start).count();
    last_frame_start = now;

    std::cout << dt * 1000.f << "ms" << std::endl;

    using namespace rasterizer;

    image_view color_buffer
    {
      .pixels = (color4ub *)draw_surface->pixels,
      .width = (std::uint32_t)width,
      .height = (std::uint32_t)height,
    };

    clear(color_buffer, {1.f, 0.3f, 1.f, 1.f});

    SDL_Rect rect = {0, 0, width, height};
    SDL_BlitSurface(draw_surface, nullptr, SDL_GetWindowSurface(window), &rect);

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}