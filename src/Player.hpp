#pragma once

#include "SDL_Helpers.hpp"
#include "Vec2.hpp"

namespace color_shootout
{
    class Player
    {
    public:
        Vec2 position;
        int32_t size = 100;

        SDL_Point center;
        float angle = 0.0F;

        SDL_Texture *texture = nullptr;

        Player() = default;
        Player(SDL_Renderer *renderer, const Vec2 position);
        ~Player();
    };
}
