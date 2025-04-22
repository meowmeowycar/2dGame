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

    // Graphics
    std::string const backgroundImage = "../../Media/backgrounds/background2.jpg";
    std::string const playerImage = "../../Media/Ludzik.png";
    std::string const wallImage = "../../Media/terrain/wall.jpg";
    std::string const healthbarImage1 = "../../Media/HUD/healthbar1.png";
    std::string const healthbarImage2 = "../../Media/HUD/healthbar2.png";
    std::string const healthbarImage3 = "../../Media/HUD/healthbar3.png";

    // fonts
    sf::Font const arial("../../Media/fonts/arial/arial.ttf");

    // Player configuration
    sf::Vector2f const player_hitbox = {42, 72};
    sf::Vector2f const player_sliding_hitbox = {42, 30};
    float const player_speed = 1;

    // HUD configuration
    bool const show_hud = true;
    bool const draw_hitboxes = false;
    sf::Vector2f const healthbar_position = {30, 30};
}