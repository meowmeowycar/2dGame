#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class MagicStaff;

class ShopKeeper : public Entity {
    bool item_sold;
    bool player_in_interaction_range;
    std::string item_name;
    sf::Text item_description;

    sf::Clock interaction_cooldown;


    sf::Texture item_texture;

public:
    ShopKeeper(float x, float y);
    ShopKeeper();

    bool load_textures() override;
    void show(sf::RenderWindow& window);
    void update(Player& player, std::vector<Obstacle*>& obstacles, float dt);

    bool interact(Player& player);
    bool checkCollision(Player& player);

    void drawMessage(sf::RenderWindow& windows);
};
