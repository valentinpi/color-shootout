#include "Enemy.hpp"

namespace color_shootout
{
    Enemy::Enemy(const Vec2 &position) : position(position)
    {
        center = { int(size) / 2, int(size) / 2 };
    }
}
