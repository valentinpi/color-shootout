#include "Tile.hpp"

namespace color_shootout
{
    Tile::Tile()
    {
        update();
    }

    Tile::Tile(Vec2 position, int32_t width, int32_t height)
    {
        this->position = position;
        this->width = width;
        this->height = height;

        update();
    }

    void Tile::update()
    {
        // Color switch
        color_counter++;

        if (color_counter == COLOR_SWITCH) {
            switch(std::rand() % 6) {
            case 0:
                color = Red;
                break;
            case 1:
                color = Yellow;
                break;
            case 2:
                color = Violet;
                break;
            case 3:
                color = Green;
                break;
            case 4:
                color = Turquoise;
                break;
            case 5:
                color = Blue;
                break;
            default:
                break;
            }

            color_counter = 0;
        }
    }

    void Tile::operator=(const Tile &tile)
    {
        position = tile.position;
        width = tile.width;
        height = tile.height;
    }
}
