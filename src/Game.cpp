#include "Game.hpp"

namespace color_shootout
{
    Game::Game()
    {
        if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0)
            throw std::exception();

        window = SDL_CreateWindow("shootout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, 
            window_height, 0);
        if (window == nullptr)
            throw std::exception();

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
            throw std::exception();

        // TODO: Develop better solution to tile placement than harcoding
        tiles[0] = Tile({ window_width / 2 - 500, window_height / 2 - 500 }, 500, 500);
        tiles[1] = Tile({ window_width / 2      , window_height / 2 - 500 }, 500, 500);
        tiles[2] = Tile({ window_width / 2 - 500, window_height / 2       }, 500, 500);
        tiles[3] = Tile({ window_width / 2      , window_height / 2       }, 500, 500);
        
        player = Player(renderer, Vec2(window_width / 2, window_height / 2));
   }

    Game::~Game()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Game::run()
    {
        running = true;

        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        running = false;
                        break;
                    default:
                        break;
                }
            }

            // Get mouse position
            int mouse_x = 0, mouse_y = 0;
            SDL_GetMouseState(&mouse_x, &mouse_y);

            // Turn player to mouse
            {
                Vec2 mouse_position(mouse_x, mouse_y);
                Vec2 mouse_to_player = mouse_position;
                mouse_to_player -= player.position;
                Vec2 up(0.0F, -1.0F);
            
                float cos_angle = up.dot(mouse_to_player) / (up.magnitude() * mouse_to_player.magnitude());
                angle = std::acos(cos_angle) * 180.0F / M_PI;
                if (mouse_to_player.x < up.x)
                    angle = 360.0F - angle;
            }

            update();
            render();
            SDL_RenderPresent(renderer);
        }
    }

    void Game::update()
    {
        for (auto &tile : tiles)
            tile.update();
    }

    void Game::render()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto &tile : tiles)
        {
            SDL_SetRenderDrawColor(renderer, (tile.color & 0xFF0000) >> 16, (tile.color & 0x00FF00) >> 8, 
                tile.color & 0x0000FF, 255);
            const SDL_Rect rect = { (int) tile.position.x, (int) tile.position.y, (int) tile.width, (int) tile.height };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderCopyEx(renderer, player.texture, nullptr, &player.dstrect, angle, &player.center, SDL_FLIP_NONE);
    }
}
