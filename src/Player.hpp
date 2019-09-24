#pragma once

#include <SDL2/SDL.h>

#include "Utils.hpp"

namespace color_shootout
{
    class Player
    {
    public:
        Vec2 position;
        SDL_Point center;
        SDL_Rect dstrect;
        SDL_Texture *texture = nullptr;

        Player() = default;
        Player(SDL_Renderer *renderer, const Vec2 position);

        void update();
    };
}
