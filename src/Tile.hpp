#pragma once

#include <cstdlib>

#include "Color.hpp"
#include "Vec2.hpp"

namespace color_shootout
{
    class Tile
    {
    public:
        Vec2 position;
        int32_t width = 0, height = 0;
        
        Color color;

        Tile();
        Tile(Vec2 position, int32_t width, int32_t height);

        void update();

        void operator=(const Tile &tile);
    private:
        const int32_t COLOR_SWITCH = 16;
        int32_t color_counter = -1;
    };
}
