#include "Player.hpp"

namespace color_shootout
{
    Player::Player(SDL_Renderer *renderer, const Vec2 position) : position(position)
    {
        center = { int(size) / 2, int(size) / 2};

        texture = generate_rect_texture(renderer, White, size, size);
    }

    Player::~Player()
    {
        SDL_DestroyTexture(texture);
    }
}
