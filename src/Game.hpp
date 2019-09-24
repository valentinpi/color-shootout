#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>

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

        float angle = 0.0;
        Player player;

        std::array<Tile, 4> tiles;

        void update();
        void render();
    };
}
