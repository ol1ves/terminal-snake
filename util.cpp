#include <util.h>

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return { x + rhs.x, y + rhs.y };
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}
