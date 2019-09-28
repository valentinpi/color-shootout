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

        for (int32_t row = 0; row < tilemap_rows; row++) {
            for (int32_t col = 0; col < tilemap_cols; col++) {
                Vec2 position = { window_width / 2 - tile_size * tilemap_cols / 2 + row * tile_size, 
                    window_height / 2 - tile_size * tilemap_rows / 2 + col * tile_size };
                tiles[row * tilemap_cols + col] = Tile(position, tile_size, tile_size);
            }
        }
        
        player.reset(new Player(renderer, Vec2(window_width / 2, window_height / 2)));

        bullet_texture = generate_rect_texture(renderer, White, Bullet::width, Bullet::height);

        enemy_texture = generate_rect_texture(renderer, Black, Enemy::size, Enemy::size);
   }

    Game::~Game()
    {
        SDL_DestroyTexture(bullet_texture);
        SDL_DestroyTexture(enemy_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Game::run()
    {
        std::cout << "Welcome to the game!\n"
            << "You can shoot by pressing the Space key. The red bar on top indicates your health points left. Try\
                to survive as long as possible by shooting the black rectangles: They are trying to kill you!"
            << std::endl;

        running = true;
        time_elapsed = SDL_GetTicks();

        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                            if (shooting_delay == 0)
                                shoot = true;
                        }
                        break;
                    default:
                        break;
                }
            }

            update();
            render();
            SDL_RenderPresent(renderer);
        }
    }

    void Game::update()
    {
        if (player->health == 0)
            return;

        if (shooting_delay > 0)
            shooting_delay--;

        enemy_spawn_counter++;

        // Player movement
        int mouse_x = 0, mouse_y = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        Vec2 mouse_position(mouse_x, mouse_y);

        Vec2 distance = mouse_position - player->position;
        const float distance_magnitude = distance.magnitude();

        if (distance_magnitude > player->size / 2) {
            // Turn player to mouse
            Vec2 up(0.0F, -1.0F);
            float cos_angle = up.dot(distance) / (up.magnitude() * distance_magnitude);
            player->angle = std::acos(cos_angle) * 180.0F / M_PI;
            if (distance.x < up.x)
                player->angle = 360.0F - player->angle;

            // Move everything else so it looks like the player is moving
            const Vec2 result = player->velocity / distance_magnitude * distance;

            for (auto &tile : tiles)
                tile.position -= result;
            for (auto &bullet : bullets)
                bullet.position -= result;
            for (auto &enemy : enemies)
                enemy.position -= result;
        }

        // Shooting
        if (shoot) {
            bullets.emplace_back(player->position, distance);
            shoot = false;
            shooting_delay = SHOOTING_DELAY_SWITCH;
        }

        for (std::size_t i = 0; i < bullets.size(); i++) {
            bullets[i].position += bullets[i].direction;

            if (int(bullets[i].position.x) < 0 || int(bullets[i].position.x) > window_width ||
                int(bullets[i].position.y) < 0 || int(bullets[i].position.y) > window_height) {
                bullets.erase(bullets.begin() + i);
                i--;
                continue;
            }

            for (std::size_t j = 0; j < enemies.size(); j++) {
                Vec2 distance = enemies[j].position - bullets[i].position;
                if (distance.magnitude() < Enemy::size / 2) {
                    bullets.erase(bullets.begin() + i);
                    i--;
                    enemies.erase(enemies.begin() + j);
                    j--;

                    enemies_shot++;

                    if (enemies_shot % 100 == 0)
                        enemies.shrink_to_fit();
                    
                    break;
                }
            }
        }

        // Enemy movement
        for (auto &enemy : enemies) {
            // Turn player to mouse
            Vec2 up(0.0F, -1.0F);
            Vec2 distance = player->position - enemy.position;
            const float distance_magnitude = distance.magnitude();

            float cos_angle = up.dot(distance) / (up.magnitude() * distance_magnitude);
            enemy.angle = std::acos(cos_angle) * 180.0F / M_PI;
            if (distance.x < up.x)
                enemy.angle = 360.0F - enemy.angle;
            
            enemy.position += enemy.velocity / distance_magnitude * distance;

            if (distance_magnitude < Player::size / 2 && player->health > 0) {
                player->health--;

                if (player->health == 0)
                    std::cout << "Game over!\n" 
                        << enemies_shot << " enemies shot!\n" 
                        << "You survived " << float(SDL_GetTicks() - time_elapsed) / 1000.0F << " seconds." 
                        << std::endl;
            }
        }

        if (enemy_spawn_counter == ENEMY_SPAWN_SWITCH) {
            Vec2 position;
            switch (std::rand() % 4) {
                case 0:
                    position.x = std::rand() % window_width;
                    position.y = -Enemy::size;
                    break;
                case 1:
                    position.x = window_width + Enemy::size;
                    position.y = std::rand() % window_height;
                    break;
                case 2:
                    position.x = std::rand() % window_width;
                    position.y = window_height + Enemy::size;
                    break;
                case 3:
                    position.x = -Enemy::size;
                    position.y = std::rand() % window_height;
                    break;
                default: break;
            }

            enemies.emplace_back(position);
            enemy_spawn_counter = 0;
        }

        for (auto &tile : tiles)
            tile.update();
    }

    void Game::render()
    {
        if (player->health == 0)
            return;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto &tile : tiles) {
            SDL_SetRenderDrawColor(renderer, (tile.color & 0xFF0000) >> 16, (tile.color & 0x00FF00) >> 8, 
                tile.color & 0x0000FF, 255);
            SDL_Rect rect = { int(tile.position.x), int(tile.position.y), int(tile.width), int(tile.height) };
            SDL_RenderFillRect(renderer, &rect);
        }

        for (auto &bullet : bullets) {
            SDL_Rect dstrect = { int(bullet.position.x) - int(bullet.width) / 2, 
                int(bullet.position.y) - int(bullet.height) / 2, int(bullet.width), int(bullet.height) };
            SDL_RenderCopyEx(renderer, bullet_texture, nullptr, &dstrect, bullet.angle, &bullet.center, SDL_FLIP_NONE);
        }

        SDL_Rect dstrect = { int(player->position.x) - int(player->size) / 2, 
            int(player->position.y) - int(player->size) / 2, int(player->size), int(player->size) };
        SDL_RenderCopyEx(renderer, player->texture, nullptr, &dstrect, player->angle, &player->center, SDL_FLIP_NONE);

        for (auto &enemy : enemies) {
            SDL_Rect dstrect = { int(enemy.position.x) - int(enemy.size) / 2, 
                int(enemy.position.y) - int(enemy.size) / 2, int(enemy.size), int(enemy.size) };
            SDL_RenderCopyEx(renderer, enemy_texture, nullptr, &dstrect, enemy.angle, &enemy.center, SDL_FLIP_NONE);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 127);
        SDL_Rect rect = { 50, 50, int(float(player->health) / 100.0F * float(window_width / 4 - 100.0F)), 25 };
        SDL_RenderFillRect(renderer, &rect);
    }
}
