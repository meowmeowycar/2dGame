#include "HUD.h"
#include <SFML/Graphics.hpp>
#include "FPS.h"
#include "configuration.h"
#include "ImageDisplay.h"
#include "char_lengths.h"
#include "Button.h"
#include "Editor.h"
#include "events.h"
#include "LevelHandler.h"

sf::Texture HUD::healthbar_texture1;
sf::Texture HUD::healthbar_texture2;
sf::Texture HUD::healthbar_texture3;

sf::Texture HUD::boss_healthbar_texture1;
sf::Texture HUD::boss_healthbar_texture2;
sf::Texture HUD::boss_healthbar_texture3;

bool HUD::show_hud = conf::show_hud;

Button HUD::respawn_button(conf::window_size_f.x / 2, conf::window_size_f.y - 200, 250, 80, "Respawn");
Button HUD::next_level_button(conf::window_size_f.x / 2, conf::window_size_f.y - 200, 250, 80, "Next Level");
Button HUD::exit_button(conf::window_size_f.x / 2, conf::window_size_f.y - 200, 250, 80, "Exit");

bool HUD::load_graphics() {
    if (!Obrazek(conf::healthbarImage1, healthbar_texture1)) {
        return false;
    }
    if (!Obrazek(conf::healthbarImage2, healthbar_texture2)) {
        return false;
    }
    if (!Obrazek(conf::healthbarImage3, healthbar_texture3)) {
        return false;
    }

    if (!Obrazek(conf::boss_healthbarImage1, boss_healthbar_texture1)) {
        return false;
    }
    if (!Obrazek(conf::boss_healthbarImage2, boss_healthbar_texture2)) {
        return false;
    }
    if (!Obrazek(conf::boss_healthbarImage3, boss_healthbar_texture3)) {
        return false;
    }

    return true;
}

void HUD::display_hud(sf::RenderWindow& window, float dt, Player& player) {
    if (show_hud) {
        if (conf::edit_mode_enabled) {
            Editor::display_grid(25, player, window);
            Editor::display_mouse_pos(player, window);
        }

        if (conf::show_FPS)
            FPS::show_fps(window, dt);

        display_healthbar(window, player);

        if (LevelHandler::getLevelType() == "normal") {
            display_enemies_number(window);
        } else if (LevelHandler::getLevelType() == "boss_fight") {
            display_boss_healthbar(window, LevelHandler::getBossHealth());
        }

        if (player.isDead()) {
            display_deathscreen(window, player);
        }

        if (LevelHandler::getEnemiesNumber() <= 0) {
            if (LevelHandler::getLevel() == 2)
                display_end_screen(window);
            else
                display_complete_screen(window);
        }
    }
}

void HUD::display_healthbar(sf::RenderWindow& window, Player& player) {
    sf::Sprite healthbar_sprite1(healthbar_texture1);
    sf::Sprite healthbar_sprite2(healthbar_texture2);
    sf::Sprite healthbar_sprite3(healthbar_texture3);

    healthbar_sprite1.setPosition(conf::healthbar_position);
    healthbar_sprite1.setScale({0.2, 0.2});

    healthbar_sprite2.setPosition({conf::healthbar_position.x + 15, conf::healthbar_position.y + 13});
    healthbar_sprite2.setScale({0.2, 0.2});

    healthbar_sprite3.setPosition({conf::healthbar_position.x + 15, conf::healthbar_position.y + 13});
    healthbar_sprite3.setTextureRect(sf::IntRect({(int) ((1 - (player.getHealth() + 1) / (conf::boss_max_health + 1)) * 1103), 0}, {(int) ((player.getHealth() + 1) / (conf::boss_max_health + 1) * 1103), 138}));
    healthbar_sprite3.setScale({0.2, 0.2});

    window.draw(healthbar_sprite2);
    if (player.getHealth() > 0)
        window.draw(healthbar_sprite3);
    window.draw(healthbar_sprite1);
}

void HUD::display_deathscreen(sf::RenderWindow& window, Player& player) {
    sf::RectangleShape grey_screen(conf::window_size_f);
    grey_screen.setFillColor(sf::Color(100, 100, 100, 100));
    window.draw(grey_screen);

    sf::Text death_message(conf::arial);
    death_message.setString("YOU DIED");
    death_message.setFillColor(sf::Color::Red);
    death_message.setPosition({(conf::window_size_f.x - calculate_string_length("arial", "YOU DIED", 100)) / 2, 200});
    death_message.setCharacterSize(100);
    window.draw(death_message);

    respawn_button.setColor(sf::Color::Red);
    respawn_button.setTextColor(sf::Color::White);

    respawn_button.updateAndShow(window);

    if (respawn_button.isReleased()) {
        player.respawn();
    }
}

void HUD::display_enemies_number(sf::RenderWindow &window) {
    unsigned int enemies_left = LevelHandler::getEnemiesNumber();

    std::stringstream ss;
    ss<<"Enemies left: "<<enemies_left;

    sf::Text enemies_text(conf::arial);
    enemies_text.setString(ss.str().c_str());
    enemies_text.setCharacterSize(50);
    enemies_text.setPosition({(conf::window_size_f.x - calculate_string_length("arial", ss.str().c_str(), 50)) / 2, 20});
    enemies_text.setFillColor(sf::Color::Red);

    window.draw(enemies_text);
}

void HUD::display_complete_screen(sf::RenderWindow& window) {
    sf::RectangleShape complete_screen_background({400, 300});
    complete_screen_background.setPosition({conf::window_size_f.x / 2, conf::window_size_f.y / 2});
    sf::RectangleShape grey_screen(conf::window_size_f);
    grey_screen.setFillColor(sf::Color(100, 100, 100, 100));
    window.draw(grey_screen);

    sf::Text level_completed_message(conf::arial);
    level_completed_message.setString("LEVEL COMPLETED");
    level_completed_message.setFillColor(sf::Color::Green);
    level_completed_message.setPosition({(conf::window_size_f.x - calculate_string_length("arial", "LEVEL COMPLETED", 100)) / 2, 200});
    level_completed_message.setCharacterSize(100);
    window.draw(level_completed_message);

    next_level_button.setColor(sf::Color::Green);
    next_level_button.setTextColor(sf::Color::Black);

    next_level_button.updateAndShow(window);

    if (next_level_button.isReleased()) {
        LevelHandler::next_level();
    }
}

void HUD::display_end_screen(sf::RenderWindow& window) {
    sf::RectangleShape complete_screen_background({400, 300});
    complete_screen_background.setPosition({conf::window_size_f.x / 2, conf::window_size_f.y / 2});
    sf::RectangleShape grey_screen(conf::window_size_f);
    grey_screen.setFillColor(sf::Color(100, 100, 100, 100));
    window.draw(grey_screen);

    sf::Text game_completed_message(conf::arial);
    game_completed_message.setString("GAME COMPLETED!");
    game_completed_message.setFillColor(sf::Color::Green);
    game_completed_message.setPosition({(conf::window_size_f.x - calculate_string_length("arial", "GAME COMPLETED!", 100)) / 2, 200});
    game_completed_message.setCharacterSize(100);
    window.draw(game_completed_message);

    exit_button.setColor(sf::Color::Black);
    exit_button.setTextColor(sf::Color::White);

    exit_button.updateAndShow(window);

    if (exit_button.isReleased()) {
        window.close();
    }
}

void HUD::display_boss_healthbar(sf::RenderWindow& window, float boss_health) {
    sf::Sprite boss_healthbar_sprite1(boss_healthbar_texture1);
    sf::Sprite boss_healthbar_sprite2(boss_healthbar_texture2);
    sf::Sprite boss_healthbar_sprite3(boss_healthbar_texture3);

    sf::Vector2f size = static_cast<sf::Vector2f>(sf::Vector2u{healthbar_texture1.getSize().x, healthbar_texture1.getSize().y});

    boss_healthbar_sprite1.setPosition(conf::boss_healthbar_position);
    boss_healthbar_sprite1.setOrigin({size.x / 2, size.y / 2});
    boss_healthbar_sprite1.setScale({conf::boss_healthbar_scale * 4 / 5, conf::boss_healthbar_scale / 2});

    boss_healthbar_sprite2.setPosition({conf::boss_healthbar_position.x + 70 * conf::boss_healthbar_scale * 4 / 5, conf::boss_healthbar_position.y + 55 * conf::boss_healthbar_scale / 2});
    boss_healthbar_sprite2.setOrigin({size.x / 2, size.y / 2});
    boss_healthbar_sprite2.setScale({conf::boss_healthbar_scale * 4 / 5, conf::boss_healthbar_scale / 2});

    boss_healthbar_sprite3.setPosition({conf::boss_healthbar_position.x + 70 * conf::boss_healthbar_scale * 4 / 5, conf::boss_healthbar_position.y + 60 * conf::boss_healthbar_scale / 2});
    boss_healthbar_sprite3.setTextureRect(sf::IntRect({(int) ((1 - (boss_health + 1) / 101) * 1103), 0}, {(int) ((boss_health + 1) / 101 * 1103), 138}));
    boss_healthbar_sprite3.setOrigin({size.x / 2, size.y / 2});
    boss_healthbar_sprite3.setScale({conf::boss_healthbar_scale * 4 / 5, conf::boss_healthbar_scale / 2});

    window.draw(boss_healthbar_sprite2);
    if (boss_health > 0)
        window.draw(boss_healthbar_sprite3);
    window.draw(boss_healthbar_sprite1);
}


void HUD::toogle_HUD() {
    show_hud = !show_hud;
}