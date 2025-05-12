#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
protected:
    float max_health;
    float health;

    bool see_player;
    short vision_direction;

    sf::Clock turn_delay;

public:
    Enemy(float x, float y, float width, float height);
    Enemy(float width, float height);

    float getHealth();
    void reduce_health(float damage);

    void update(Player& player, std::vector<Obstacle>& obstacles, float dt);
    void check_vision(Player& player, std::vector<Obstacle>& obstacles);

    void show(sf::RenderWindow& window);
};