#include <SDL.h>
#include <bits/stl_algobase.h>

int main(int argv, char** args)
{
    SDL_Init(SDL_INIT_VIDEO);

    int width = 800;
    int height = 600;

    SDL_Window *window = SDL_CreateWindow(
        "My first rasterizer!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

    int mouse_x = 0;
    int mouse_y = 0;

    SDL_Surface * draw_surface = nullptr;

    bool running = true;
    while (running)
    {
        // Handle events, such as closing the window, or moving the mouse, etc.
        for (SDL_Event event; SDL_PollEvent(&event);)
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
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
        
        if (!draw_surface)
        {
            // RGBA32 means 8 bits per channel, 32 bits total.
            draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
            // Fully opaque pixels.
            SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_BLEND);
        }

        SDL_Rect rect = { 0, 0, width, height };
        SDL_BlitSurface(draw_surface, nullptr, SDL_GetWindowSurface(window), &rect);

        SDL_UpdateWindowSurface(window);

        std::fill_n((uint32_t *)draw_surface->pixels, width * height, 0xffffdfdf);
    }

    return 0;
}