#pragma once

#include <cstdint>
#include <cstdlib>

#include "Utils.hpp"

namespace color_shootout
{
    enum TileColor
    {
        RED = 0xFF0000,
        YELLOW = 0xFFFF00,
        VIOLET = 0xFF00FF,
        GREEN = 0x00FF00,
        TURQUOISE = 0x00FFFF,
        BLUE = 0x0000FF
    };

    class Tile
    {
    public:
        Vec2 position;
        uint32_t width = 0, height = 0;
        TileColor color;

        Tile();
        Tile(Vec2 position, uint32_t width, uint32_t height);

        void update();

        void operator=(const Tile &tile);
    private:
        const int32_t COLOR_SWITCH = 16;
        int32_t color_counter = -1;
    };
}
