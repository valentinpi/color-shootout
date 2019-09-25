#pragma once

#include <cmath>
#include <cstdint>

namespace color_shootout
{
    struct Vec2
    {
        float x = 0.0F, y = 0.0F;

        Vec2() = default;
        Vec2(const Vec2 &other);
        Vec2(const float x, const float y);
        Vec2(const int32_t x, const int32_t y);

        float dot(const Vec2 &other) const;
        float magnitude() const;

        Vec2 operator+ (const Vec2 &other) const;
        void operator+=(const Vec2 &other);
        Vec2 operator- (const Vec2 &other) const;
        void operator-=(const Vec2 &other);
        Vec2 operator* (const float &scalar) const;
        void operator*=(const float &scalar);
    };

    Vec2 operator*(const float &left, const Vec2 &right);
}
