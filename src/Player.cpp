#include "Player.hpp"

namespace color_shootout
{
    Player::Player(SDL_Renderer *renderer, const Vec2 position)
    {
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
        SDL_SetRenderTarget(renderer, texture);

        Uint8 prev_r = 0, prev_g = 0, prev_b = 0, prev_a = 0;
        SDL_GetRenderDrawColor(renderer, &prev_r, &prev_g, &prev_b, &prev_a);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect rect = { 0, 0, 100, 100 };
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        SDL_SetRenderDrawColor(renderer, prev_r, prev_g, prev_b, prev_a);

        SDL_SetRenderTarget(renderer, nullptr);
        this->position = position;
        center.x = 50;
        center.y = 50;
        dstrect.x = position.x - 50;
        dstrect.y = position.y - 50;
        dstrect.w = 100;
        dstrect.h = 100;
    }

    void Player::update()
    {
        
    }
}
