#include "ShopKeeper.h"
#include "ImageDisplay.h"
#include "configuration.h"
#include <iostream>
#include "LevelHandler.h"
#include "Player.h"
#include "char_lengths.h"
#include <cmath>
#include "MagicStaff.h"

ShopKeeper::ShopKeeper(float x, float y) : Entity(x, y, conf::shopkeeper_hitbox.x, conf::shopkeeper_hitbox.y), player_in_interaction_range(false), item_sold(false),
                                           item_name("Magic Staff"), item_description(conf::arial, "Magic Staff", 20) {


    item_description.setFillColor(sf::Color::Yellow);

}

ShopKeeper::ShopKeeper() : ShopKeeper(0, 0){}

bool ShopKeeper::load_textures() {
    if (!Obrazek(conf::shopkeeperImage, entity_texture)) {
        return false;
    }

    if (!Obrazek(conf::magicStaffImage, item_texture)) {
        return false;
    }

    return true;
}

bool ShopKeeper::checkCollision(Player& player) {

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f playerHitbox = player.getHitbox();

    float dx = std::abs(playerPos.x - position.x);
    float dy = std::abs(playerPos.y - position.y);

    //interakcja range
    if (dx < playerHitbox.x / 2 + hitbox.x / 2 && dy < playerHitbox.y / 2 + hitbox.y / 2) {
        return true;
    }
    return false;
}

void ShopKeeper::update(Player& player, std::vector<Obstacle*>& obstacles, float dt) {
    Entity::update(obstacles, dt);

    player_in_interaction_range = checkCollision(player);

    if (player_in_interaction_range && isKeyPressed(::sf::Keyboard::Key::E) && interaction_cooldown.getElapsedTime().asSeconds() > 0.5f) {
        interaction_cooldown.restart();
        interact(player);
    }
}

bool ShopKeeper::interact(Player& player) {
    if (!item_sold) {
        player.acquiredMagicStaff();
        std::cout << "Item received " << item_name << std::endl;

        item_sold = true;
        return true;
    }

    return false;
}

void ShopKeeper::show(sf::RenderWindow& window) {
    Entity::show(window);

    if (draw_hitboxes) {
        draw_hitbox(window);
    }

    if (player_in_interaction_range && !item_sold) {
        sf::Text interaction(conf::arial, "Press E to interact with the shopkeeper");
        interaction.setFillColor(sf::Color::Red);
        interaction.setOutlineColor(sf::Color::Black);
        interaction.setCharacterSize(30);
        interaction.setOutlineThickness(2);
        interaction.setPosition({position.x - calculate_string_length("arial", "Press E to interact", 30) / 2, position.y - 200});
        window.draw(interaction);
    }

    if (item_sold) {
        sf::Text sold_text(conf::arial);
        sold_text.setFillColor(sf::Color::Red);
        sold_text.setOutlineColor(sf::Color::Black);
        sold_text.setCharacterSize(30);
        sold_text.setOutlineThickness(2);
        sold_text.setString("Sold out");
        sold_text.setPosition({position.x - calculate_string_length("arial", "Sold out", 30) / 2, position.y - 200});
        window.draw(sold_text);
    }
}

