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
    std::string const boss_healthbarImage1 = "../../Media/HUD/boss_healthbar1.png";
    std::string const boss_healthbarImage2 = "../../Media/HUD/boss_healthbar2.png";
    std::string const boss_healthbarImage3 = "../../Media/HUD/boss_healthbar3.png";
    std::string const arrowImage = "../../Media/entities/Arrow.png";
    std::string const stalkerImage = "../../Media/entities/Stalker.png";
    std::string const archerImage = "../../Media/entities/Archer.png";
    std::string const sprinterImage = "../../Media/entities/Sprinter_stay.png";
    std::string const sprinterImage2 = "../../Media/entities/Sprinter_run.png";
    std::string const bossImage = "../../Media/entities/Sprinter_stay.png";
    std::string const swordImage = "../../Media/items/sword.png";
    std::string const cursorImage = "../../Media/cursors/cursor1.png";
    std::string const checkpointImage = "../../Media/enviroment/checkpoint.png";
    std::string const shopkeeperImage = "../../Media/entities/shopkeeper.png";
    std::string const magicStaffImage = "../../Media/items/magicStaff.png";
    std::string const magicProjectileImage = "../../Media/items/Projectile.png";

    // fonts
    sf::Font const arial("../../Media/fonts/arial/arial.ttf");

    // Player configuration
    sf::Vector2f const player_hitbox = {50, 100};
    sf::Vector2f const player_sliding_hitbox = {42, 30};
    float const jump_strength = 1100;
    float const player_speed = 200;

    //Terrain
    sf::Vector2f const checkpoint_hitbox = {200, 200};
    bool const show_message = true;
    float const message_display_time = 3.0f;
    std::string const save_directory = "../../saves/";

    //items
    sf::Vector2f const sword_hitbox = {100, 30};
    sf::Vector2f const magicStaff_hitbox = {30, 100};
    sf::Vector2f const magicProjectile_hitbox = {50, 50};
    const float magic_projectile_speed = 1500.0f;

    // Enemies configuration
    float const default_vision_distance = 500;
    float const default_back_vision_distance = 200;
    bool const disable_vision = edit_mode_enabled;

    // Stalker configuration
    sf::Vector2f const stalker_hitbox = {75, 150};
    float const stalker_damage = 10;
    float const stalker_vision_distance = default_vision_distance;
    float const stalker_back_vision_distance = default_back_vision_distance;

    // Archer configuration
    sf::Vector2f const archer_hitbox = {75, 150};
    float const archer_damage = 10;
    sf::Vector2f const arrow_hitbox = {10, 10};
    float const arrow_speed = 800;
    float const archer_vision_distance = 800;
    float const archer_back_vision_distance = archer_vision_distance;

    // Sprinter configuration
    sf::Vector2f const sprinter_hitbox = {110, 150};
    float const sprinter_damage = 10;
    float const charge_time = 2;
    float const sprinter_vision_distance = default_vision_distance;
    float const sprinter_back_vision_distance = default_back_vision_distance;
    float const dash_distance = sprinter_vision_distance;

    // Boss configuration
    sf::Vector2f const boss_hitbox = {500, 700};
    float const boss_max_health = 100;
    float const boss_arrow_damage = 5;
    float const boss_vision_distance = 1000;
    float const boss_back_vision_distance = boss_vision_distance;

    //ShopKeeper
    sf::Vector2f const shopkeeper_hitbox = {75, 75};

    // HUD configuration
    bool const show_hud = true;
    bool const draw_hitboxes = true;
    sf::Vector2f const healthbar_position = {30, 30};
    float const boss_healthbar_scale = 1;
    sf::Vector2f const boss_healthbar_position = {window_size_f.x / 2, 100 * boss_healthbar_scale};

    //pauseMenu configuration
    bool const show_pausemenu = false;

    // Physics configuration
    float const gravity_force = 9.8f * 200;
}