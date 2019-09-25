#pragma once

#include <SDL2/SDL.h>

#include "Utils.hpp"

namespace color_shootout
{
    /*
    struct Bullet
    {
        Vec2 position;
        Vec2 direction;
        static const int32_t width = 25, height = 10;
        float velocity = 20.0F, angle = 0.0F;

        Bullet(const Vec2 &position, const Vec2 &direction);
    };
    */

    class Player
    {
    public:
        Vec2 position;
        SDL_Point center;
        int32_t size = 100;
        float angle = 0.0F;
        SDL_Texture *texture = nullptr;

        Player() = default;
        Player(SDL_Renderer *renderer, const Vec2 position);
        ~Player();
    };
}
