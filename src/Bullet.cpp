#include "Bullet.hpp"

namespace color_shootout
{
    Bullet::Bullet(const Vec2 &position, const Vec2 &direction) : position(position)
    {
        this->direction = velocity / direction.magnitude() * direction;
        
        Vec2 up(0.0F, -1.0F);
        float cos_angle = up.dot(this->direction) / (up.magnitude() * this->direction.magnitude());
        angle = std::acos(cos_angle) * 180.0F / M_PI;
        if (this->direction.x < up.x)
            angle = 360.0F - angle;

        center = { int(width) / 2, int(height) / 2 };
    }
}
