#pragma once
#include <SFML/Graphics.hpp>

namespace conf {
    // window configuration
    sf::Vector2u const window_size = {1920, 1080};
    sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
    int const max_framerate = 1000;
    float dt = 1.0f / static_cast<float>(max_framerate);
}