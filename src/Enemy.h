#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
protected:
    float max_health;
    float health;

    bool see_player;
    short vision_direction;

    float vision_distance;
    float back_vision_distance;

    sf::Clock turn_delay;
    sf::Clock hit_effect_delay;

public:
    Enemy(float x, float y, float width, float height, short vision_direction);
    Enemy(float x, float y, float width, float height);
    Enemy(float width, float height);

    float getHealth();
    std::string getType();
    void reduce_health(float damage);

    virtual void update(Player& player, std::vector<Obstacle*>& obstacles, float dt);
    void check_vision(Player& player, std::vector<Obstacle*>& obstacles);

    virtual void show(sf::RenderWindow& window);
};