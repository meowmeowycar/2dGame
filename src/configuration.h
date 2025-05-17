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

    // Tools
    bool const edit_mode_enabled = false;

    // Graphics
    std::string const backgroundImage = "../../Media/backgrounds/background2.jpg";
    std::string const optionsMenuBackgroundImage = "../../Media/backgrounds/MenuOptionsBack.png";
    std::string const mainMenuBackgroundImage = "../../Media/backgrounds/MainMenuBack.jpg";
    std::string const playerImage = "../../Media/entities/Aura.png";
    std::string const wallImage = "../../Media/terrain/wall3.jpg";
    std::string const semiWallImage1 = "../../Media/terrain/semi_wall1.png";
    std::string const semiWallImage2 = "../../Media/terrain/semi_wall2.png";
    std::string const semiWallImage3 = "../../Media/terrain/semi_wall3.png";
    std::string const healthbarImage1 = "../../Media/HUD/healthbar1.png";
    std::string const healthbarImage2 = "../../Media/HUD/healthbar2.png";
    std::string const healthbarImage3 = "../../Media/HUD/healthbar3.png";
    std::string const arrowImage = "../../Media/entities/Arrow.png";
    std::string const stalkerImage = "../../Media/entities/enemy.png";
    std::string const archerImage = "../../Media/entities/Archer.png";
    std::string const sprinterImage = "../../Media/entities/Stalker_stay.png";
    std::string const sprinterImage2 = "../../Media/entities/Stalker_run.png";
    std::string const swordImage = "../../Media/items/sword.png";
    std::string const cursorImage = "../../Media/cursors/cursor1.png";

    // fonts
    sf::Font const arial("../../Media/fonts/arial/arial.ttf");

    // Player configuration
    sf::Vector2f const player_hitbox = {50, 100};
    sf::Vector2f const player_sliding_hitbox = {42, 30};
    float const jump_strength = 1100;
    float const player_speed = 200;

    //items
    sf::Vector2f const sword_hitbox = {100, 40};

    // Enemies configuration
    float const vision_distance = 500;
    float const back_vision_distance = 200;

    // Stalker configuration
    sf::Vector2f const stalker_hitbox = {75, 150};
    float const stalker_damage = 10;

    // Archer configuration
    sf::Vector2f const archer_hitbox = {75, 150};
    float const archer_damage = 10;
    sf::Vector2f const arrow_hitbox = {50, 50};
    float const arrow_speed = 800;

    // Sprinter configuration
    sf::Vector2f const sprinter_hitbox = {75, 150};
    float const sprinter_damage = 10;
    float const charge_time = 2;
    float const dash_distance = vision_distance;

    // HUD configuration
    bool const show_hud = true;
    bool const draw_hitboxes = true;
    sf::Vector2f const healthbar_position = {30, 30};

    //pauseMenu configuration
    bool const show_pausemenu = false;

    // Physics configuration
    float const gravity_force = 9.8f * 200;
}