#pragma once

#include <SDL2/SDL.h>

#include "Color.hpp"

namespace color_shootout
{
    // color: RGB value
    SDL_Texture *generate_rect_texture(SDL_Renderer *renderer, Color color, int32_t width, int32_t height);
}
