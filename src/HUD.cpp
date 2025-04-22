#include "HUD.h"
#include <SFML/Graphics.hpp>
#include "FPS.h"
#include "configuration.h"
#include "ImageDisplay.h"

sf::Texture HUD::healthbar_texture1;
sf::Texture HUD::healthbar_texture2;
sf::Texture HUD::healthbar_texture3;

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
    if (conf::show_FPS)
        FPS::show_fps(window, dt);

    display_healthbar(window, player);
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
    window.draw(healthbar_sprite3);
    window.draw(healthbar_sprite1);
}