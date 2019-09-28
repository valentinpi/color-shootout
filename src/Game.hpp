#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "SDLHelpers.hpp"
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
        uint32_t time_elapsed = 0;

        int32_t tile_size = 500, tilemap_rows = 4, tilemap_cols = 4;
        std::array<Tile, 16> tiles;
        
        std::unique_ptr<Player> player = nullptr;
        
        bool shoot = false;
        static const int32_t SHOOTING_DELAY_SWITCH = 32;
        int32_t shooting_delay = 0;
        int32_t enemies_shot = 0;
        std::vector<Bullet> bullets;
        SDL_Texture *bullet_texture = nullptr;

        static const int32_t ENEMY_SPAWN_SWITCH = 80;
        int32_t enemy_spawn_counter = 0;
        std::vector<Enemy> enemies;
        SDL_Texture *enemy_texture = nullptr;

        void update();
        void render();
    };
}
