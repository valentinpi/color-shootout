#pragma once

#include "SDLHelpers.hpp"
#include "Vec2.hpp"

namespace color_shootout
{
    class Player
    {
    public:
        Vec2 position;
        static const int32_t size = 100;

        float velocity = 5.0F;

        SDL_Point center;
        float angle = 0.0F;

        SDL_Texture *texture = nullptr;

        int32_t health = 100;

        Player() = default;
        Player(SDL_Renderer *renderer, const Vec2 &position);
        ~Player();
    };
}
