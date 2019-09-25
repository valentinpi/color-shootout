#include "Game.hpp"

namespace color_shootout
{
    Game::Game()
    {
        if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0)
            throw std::exception();

        window = SDL_CreateWindow("color-shootout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, 
            window_height, 0);
        if (window == nullptr)
            throw std::exception();

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
            throw std::exception();

        for (int32_t row = 0; row < tilemap_rows; row++)
        {
            for (int32_t col = 0; col < tilemap_cols; col++)
            {
                Vec2 position = { window_width / 2 - tile_size * tilemap_cols / 2 + row * tile_size, 
                    window_height / 2 - tile_size * tilemap_rows / 2 + col * tile_size };
                tiles[row * tilemap_cols + col] = Tile(position, tile_size, tile_size);
            }
        }

        bullet_texture = generate_rect_texture(renderer, White, Bullet::width, Bullet::height);
        
        player.reset(new Player(renderer, Vec2(window_width / 2, window_height / 2)));
   }

    Game::~Game()
    {
        SDL_DestroyTexture(bullet_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Game::run()
    {
        running = true;

        while (running)
        {
            bool shoot = false;

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                            shoot = true;
                        break;
                    default:
                        break;
                }
            }

            // Get mouse position
            int mouse_x = 0, mouse_y = 0;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            Vec2 mouse_position(mouse_x, mouse_y);

            {
                Vec2 distance = mouse_position;
                distance -= player->position;
                float distance_magnitude = distance.magnitude();

                if (distance_magnitude > player->size / 2)
                {
                    // Turn player to mouse
                    Vec2 up(0.0F, -1.0F);
                    float cos_angle = up.dot(distance) / (up.magnitude() * distance_magnitude);
                    player->angle = std::acos(cos_angle) * 180.0F / M_PI;
                    if (distance.x < up.x)
                        player->angle = 360.0F - player->angle;

                    // Move player
                    for (auto &tile : tiles)
                        tile.position -= (5.0F / distance_magnitude * distance);
                }

                if (shoot)
                    bullets.emplace_back(player->position, distance);
            }

            for (std::size_t i = 0; i < bullets.size(); i++)
            {
                bullets[i].position += bullets[i].direction;

                if (int(bullets[i].position.x) < 0 || int(bullets[i].position.x) > window_width ||
                    int(bullets[i].position.y) < 0 || int(bullets[i].position.y) > window_height)
                {
                    bullets.erase(bullets.begin() + i);
                    i--;
                }
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
            SDL_Rect rect = { int(tile.position.x), int(tile.position.y), int(tile.width), int(tile.height) };
            SDL_RenderFillRect(renderer, &rect);
        }

        for (auto &bullet : bullets)
        {
            SDL_Rect dstrect = { int(bullet.position.x) - int(bullet.width) / 2, 
                int(bullet.position.y) - int(bullet.height) / 2, int(bullet.width), int(bullet.height) };
            SDL_RenderCopyEx(renderer, bullet_texture, nullptr, &dstrect, bullet.angle, &bullet.center, SDL_FLIP_NONE);
        }

        SDL_Rect dstrect = { int(player->position.x) - int(player->size) / 2, 
            int(player->position.y) - int(player->size) / 2, int(player->size), int(player->size) };
        SDL_RenderCopyEx(renderer, player->texture, nullptr, &dstrect, player->angle, &player->center, SDL_FLIP_NONE);
    }
}
