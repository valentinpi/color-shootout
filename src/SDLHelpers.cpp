#include "SDLHelpers.hpp"

namespace color_shootout
{
    SDL_Texture *generate_rect_texture(SDL_Renderer *renderer, Color color, int32_t width, int32_t height)
    {
        SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, 
            height);

        Uint8 prev_r = 0, prev_g = 0, prev_b = 0, prev_a = 0;
        SDL_GetRenderDrawColor(renderer, &prev_r, &prev_g, &prev_b, &prev_a);
        SDL_SetRenderDrawColor(renderer, (color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF, 255);
        SDL_Texture *prev_target = SDL_GetRenderTarget(renderer);
        SDL_SetRenderTarget(renderer, texture);

        SDL_Rect rect = { 0, 0, int(width), int(height) };
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        SDL_SetRenderTarget(renderer, prev_target);
        SDL_SetRenderDrawColor(renderer, prev_r, prev_g, prev_b, prev_a);
        
        return texture;
    }
}
