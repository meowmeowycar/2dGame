#pragma once
#include <string>

namespace conf {
    // window configuration
    sf::Vector2u const window_size = {1920, 1080};
    sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
    bool const limit_framerate = true;
    int const max_framerate = 144;
    float const dt = 1.0f / max_framerate;
    bool const show_FPS = true;
    int const fps_accuracy = 100;

    // fonts
    sf::Font const arial("../../Media/fonts/arial/arial.ttf");

    // Player configuration
    std::string const playerImagePath = "../../Media/Ludzik.png";
}