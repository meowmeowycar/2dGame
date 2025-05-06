#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <vector>
#include "Entity.h"

class Player : public Entity {
    float health;
    bool sliding;

public:
    Player(float x, float y);
    Player();

    void update(std::vector<Obstacle>& obstacles, float dt);
    void reduce_health(float damage);

    float getHealth();
};