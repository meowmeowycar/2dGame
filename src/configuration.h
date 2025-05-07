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
    std::string const arrowImage = playerImage;

    // fonts
    sf::Font const arial("../../Media/fonts/arial/arial.ttf");

    // Player configuration
    sf::Vector2f const player_hitbox = {42, 72};
    sf::Vector2f const player_sliding_hitbox = {42, 30};

    // Enemies configuration
    float const vision_distance = 500;
    float const back_vision_distance = 200;

    // Stalker configuration
    sf::Vector2f const stalker_hitbox = {50, 100};
    float const stalker_damage = 10;

    // Archer configuration
    sf::Vector2f const archer_hitbox = {50, 100};
    float const archer_damage = 10;
    sf::Vector2f const arrow_hitbox = {50, 20};
    float const arrow_speed = 1000;

    // Sprinter configuration
    sf::Vector2f const sprinter_hitbox = player_hitbox;
    float const sprinter_damage = 100;
    float const charge_time = 2;
    float const dash_distance = vision_distance;

    // HUD configuration
    bool const show_hud = true;
    bool const draw_hitboxes = true;
    sf::Vector2f const healthbar_position = {30, 30};

    // Physics configuration
    float const gravity_force = 980.0f * 144;
}