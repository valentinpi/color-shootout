#include "Tile.hpp"

namespace color_shootout
{
    Tile::Tile()
    {
        update();
    }

    Tile::Tile(Vec2 position, uint32_t width, uint32_t height)
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

        if (color_counter == COLOR_SWITCH)
        {
            switch((int32_t) std::rand() % 6)
            {
                case 0:
                    color = RED;
                    break;
                case 1:
                    color = YELLOW;
                    break;
                case 2:
                    color = VIOLET;
                    break;
                case 3:
                    color = GREEN;
                    break;
                case 4:
                    color = TURQUOISE;
                    break;
                case 5:
                    color = BLUE;
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
