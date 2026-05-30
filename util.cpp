/**
 * @file util.cpp
 * @author Oliver Santana
 * @brief Utility implementations for snake game.
 */

#include "util.h"

Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}
