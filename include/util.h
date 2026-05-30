/**
 * @file util.h
 * @author Oliver Santana
 * @brief Utility header for snake game.
 */

#ifndef UTIL_H
#define UTIL_H

struct Vec2 {
    int x;
    int y;

    /**
     * @brief Adds two Vec2 objects together and returns result as a new Vec2.
     * @param rhs The right-hand side Vec2 to add to this Vec2.
     * @return A new Vec2 that is the sum of this Vec2 and rhs.
     */
    Vec2 operator+(const Vec2& rhs) const; 

    /**
     * @brief Adds another Vec2 to this Vec2 in-place.
     * @param rhs The right-hand side Vec2 to add to this Vec2.
     * @return A reference to this Vec2 after addition.
     */
    Vec2& operator+=(const Vec2& rhs);
};

#endif