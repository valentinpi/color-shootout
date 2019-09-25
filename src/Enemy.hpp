#pragma once

#include <SDL2/SDL.h>

#include "Vec2.hpp"

namespace color_shootout
{
    class Enemy
    {
    public:
        Vec2 position;
        static const int32_t size = 100;

        float velocity = 10.0F;

        SDL_Point center;
        float angle = 0.0F;

        SDL_Texture *texture = nullptr;

        Enemy() = default;
        Enemy(const Vec2 &position);
    };
}
