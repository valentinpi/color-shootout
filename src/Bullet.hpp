#pragma once

#include <cmath>

#include <SDL2/SDL.h>

#include "Vec2.hpp"

namespace color_shootout
{
    class Bullet
    {
    public:
        Vec2 position;
        static const int32_t width = 10, height = 30;

        SDL_Point center;
        float angle = 0.0F;

        Vec2 direction;

        Bullet(const Vec2 &position, const Vec2 &direction);
    private:
        float velocity = 20.0F;
    };
}
