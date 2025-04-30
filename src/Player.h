#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <vector>
#include "Entity.h"

class Player : public Entity {
    float health;
    bool sliding;

public:
    Player();
    Player(float x, float y);

    void update (std::vector<Obstacle>& obstacles, float dt);
    float getHealth();
};