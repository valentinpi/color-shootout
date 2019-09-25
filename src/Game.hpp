#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <exception>
#include <memory>
#include <vector>

#include "Bullet.hpp"
#include "Player.hpp"
#include "SDL_Helpers.hpp"
#include "Tile.hpp"

namespace color_shootout
{
    class Game
    {
    public:
        Game();
        ~Game();

        void run();
    private:
        SDL_Window *window = nullptr;
        int32_t window_width = 1280, window_height = 720;
        SDL_Renderer *renderer = nullptr;
        bool running = false;

        int32_t tile_size = 500, tilemap_rows = 4, tilemap_cols = 4;
        std::array<Tile, 16> tiles;
        
        std::vector<Bullet> bullets;
        SDL_Texture *bullet_texture = nullptr;
        
        std::unique_ptr<Player> player = nullptr;

        void update();
        void render();
    };
}
