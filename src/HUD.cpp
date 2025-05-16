#include "HUD.h"
#include <SFML/Graphics.hpp>
#include "FPS.h"
#include "configuration.h"
#include "ImageDisplay.h"
#include "Button.h"
#include "events.h"

sf::Texture HUD::healthbar_texture1;
sf::Texture HUD::healthbar_texture2;
sf::Texture HUD::healthbar_texture3;

bool HUD::show_hud = conf::show_hud;

Button HUD::respawn_button(conf::window_size_f.x / 2, conf::window_size_f.y - 200, 200, 60, "Respawn");

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

    return true;
}

void HUD::display_hud(sf::RenderWindow& window, float dt, Player& player) {
    if (show_hud) {
        if (conf::show_FPS)
            FPS::show_fps(window, dt);

        display_healthbar(window, player);

        if (player.isDead()) {
            display_deathscreen(window, player);
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
    healthbar_sprite3.setTextureRect(sf::IntRect({(int) ((1 - (player.getHealth() + 1) / 101) * 1103), 0}, {(int) ((player.getHealth() + 1) / 101 * 1103), 138}));
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
    death_message.setPosition({700, 200});
    death_message.setCharacterSize(100);
    window.draw(death_message);

    respawn_button.setColor(sf::Color::Red);
    respawn_button.setTextColor(sf::Color::White);

    respawn_button.updateAndShow(window);

    if (respawn_button.isReleased()) {
        player.respawn();
    }
}

void HUD::toogle_HUD() {
    show_hud = !show_hud;
}