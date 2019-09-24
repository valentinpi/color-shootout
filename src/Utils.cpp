#include "Utils.hpp"

namespace color_shootout
{
    Vec2::Vec2(const Vec2 &other)
    {
        *this = other;
    }

    Vec2::Vec2(const float x, const float y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2::Vec2(const int32_t x, const int32_t y)
    {
        this->x = x;
        this->y = y;
    }

    float Vec2::dot(const Vec2 &other)
    {
        return x * other.x + y * other.y;
    }

    float Vec2::magnitude()
    {
        return std::sqrt(x * x + y * y);
    }

    void Vec2::operator-=(const Vec2 &other)
    {
        x -= other.x;
        y -= other.y;
    }
}
