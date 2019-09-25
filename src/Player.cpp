#include "Player.hpp"

namespace color_shootout
{
    /*
    Bullet::Bullet(const Vec2 &position, const Vec2 &direciton) : position(position)
    {
        this->direction = velocity / direction.magnitude() * direction;
    }
    */

    Player::Player(SDL_Renderer *renderer, const Vec2 position) : position(position)
    {
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, int(size), int(size));

        SDL_SetRenderTarget(renderer, texture);
        Uint8 prev_r = 0, prev_g = 0, prev_b = 0, prev_a = 0;
        SDL_GetRenderDrawColor(renderer, &prev_r, &prev_g, &prev_b, &prev_a);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect rect = { 0, 0, int(size), int(size) };
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        SDL_SetRenderDrawColor(renderer, prev_r, prev_g, prev_b, prev_a);
        SDL_SetRenderTarget(renderer, nullptr);

        center = { int(size) / 2, int(size) / 2 };
    }

    Player::~Player()
    {
        SDL_DestroyTexture(texture);
    }
}
