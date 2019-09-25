#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "SDL2/SDL.h"

#include "Player.hpp"
#include "Tile.hpp"
#include "Utils.hpp"

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

        int32_t tile_size = 1000, tilemap_rows = 4, tilemap_cols = 4;
        std::array<Tile, 16> tiles;
        // SDL_Texture *bullet_texture = nullptr;
        // std::vector<Bullet> bullets;
        std::unique_ptr<Player> player = nullptr;

        void update();
        void render();
    };
}
