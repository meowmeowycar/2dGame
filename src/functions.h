#pragma once
#include <SFML/Graphics.hpp>

inline short sign(float x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

inline float calculate_distance(sf::Vector2f v1, sf::Vector2f v2) {
    return sf::Vector2f(v1.x - v2.x, v1.y - v2.y).length();
}