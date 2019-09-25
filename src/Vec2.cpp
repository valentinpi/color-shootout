#include "Vec2.hpp"

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

    float Vec2::dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    float Vec2::magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vec2 Vec2::operator+ (const Vec2 &other) const
    {
        Vec2 result(x + other.x, y + other.y);
        return result;
    }

    void Vec2::operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;
    }

    Vec2 Vec2::operator- (const Vec2 &other) const
    {
        Vec2 result(x - other.x, y - other.y);
        return result;
    }

    void Vec2::operator-=(const Vec2 &other)
    {
        x -= other.x;
        y -= other.y;
    }

    Vec2 Vec2::operator* (const float &scalar) const
    {
        Vec2 result(x * scalar, y * scalar);
        return result;
    }

    void Vec2::operator*=(const float &scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    Vec2 operator*(const float &left, const Vec2 &right)
    {
        Vec2 result(left * right.x, left * right.y);
        return result;
    }
}
